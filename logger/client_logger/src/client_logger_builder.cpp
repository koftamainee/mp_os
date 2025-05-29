#include "../include/client_logger_builder.h"
#include "../include/client_logger.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

client_logger_builder::client_logger_builder() {
  std::pair<logger::severity, std::string> severities[6] = {
      {logger::severity::trace, "trace"},
      {logger::severity::debug, "debug"},
      {logger::severity::information, "information"},
      {logger::severity::warning, "warning"},
      {logger::severity::error, "error"},
      {logger::severity::critical, "critical"},
  };

  for (auto const &severity : severities) {
    _streams_info[severity.first] =
        std::make_pair(std::set<std::string>(), severity.second);
  }

  _log_format = "[%d %t][%s] %m";
}

logger_builder *
client_logger_builder::set_log_format(std::string const &format) {
  const std::set<char> valid_placeholders = {'d', 't', 's', 'm'};

  for (int i = 0; i < format.length(); ++i) {
    if (format[i] == '%') {
      if (i + 1 >= format.length()) {
        throw std::invalid_argument(
            "Incomplete placeholder at end of format string");
      }
      char placeholder = format[i + 1];
      if (valid_placeholders.find(placeholder) == valid_placeholders.end()) {
        throw std::invalid_argument("Invalid placeholder %" +
                                    std::string(1, placeholder));
      }
      ++i;
    }
  }

  _log_format = format;
  return this;
}

logger_builder *
client_logger_builder::add_file_stream(std::string const &stream_file_path,
                                       logger::severity severity) {
  if (stream_file_path.empty()) {
    throw std::invalid_argument("File path cannot be empty");
  }
  if (stream_file_path.find_first_of("\"*<>?|") != std::string::npos) {
    throw std::invalid_argument("File path contains invalid characters");
  }

  _streams_info[severity].first.insert(convert_to_absolute(stream_file_path));

  return this;
}

logger_builder *
client_logger_builder::add_console_stream(logger::severity severity) {
  _streams_info[severity].first.insert("");

  return this;
}

logger_builder *client_logger_builder::transform_with_configuration(
    std::string const &configuration_file_path,
    std::string const &configuration_path) {
  std::ifstream config_file(configuration_file_path);

  nlohmann::json parsed_config;
  config_file >> parsed_config;

  std::stringstream configuration_path_stream(configuration_path);

  std::string configuration_path_part;
  while (
      std::getline(configuration_path_stream, configuration_path_part, ':')) {
    if (std::isdigit(configuration_path_part[0])) {
      parsed_config = parsed_config.at(std::stoi(configuration_path_part));
    } else {
      parsed_config = parsed_config.at(configuration_path_part);
    }
  }

  set_log_format(parsed_config.at("format"));

  auto streams_config_section = parsed_config.at("streams");
  for (auto const stream_config_section : streams_config_section) {
    std::string target_file_absolute_path;
    auto path_from_config = stream_config_section.at("path");
    if (path_from_config == "") {
      target_file_absolute_path = std::move(path_from_config);
    } else {

      convert_to_absolute(path_from_config);
    }

    auto stream_severities_config_section =
        stream_config_section.at("severities");
    logger::severity temp;
    for (auto const stream_severity_config_section :
         stream_severities_config_section) {
      for (auto item : _streams_info) {
        if (item.second.second ==
            stream_severity_config_section.get<std::string>()) {
          temp = item.first;
          break;
        }
      }

      _streams_info[temp].first.insert(target_file_absolute_path);
    }
  }

  return this;
}

logger_builder *client_logger_builder::clear() {
  *this = client_logger_builder();

  return this;
}

logger *client_logger_builder::build() const {
  return new client_logger(_streams_info, _log_format);
}

std::string
client_logger_builder::convert_to_absolute(std::string const &path) {

  std::filesystem::path fs_path = path;

  return std::filesystem::absolute(fs_path).string();

  return path;
}
