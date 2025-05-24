#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H

#include <map>
#include <ostream>
#include <set>
#include <vector>

#include "logger.h"
#include <client_logger_builder.h>

class client_logger final : public logger {

  friend class client_logger_builder;

private:
  static std::map<std::string, std::pair<std::ostream *, size_t>> _all_streams;

private:
  std::map<logger::severity,
           std::vector<std::pair<std::ostream *, std::string>>>
      _streams;
  std::string _log_format;

private:
  explicit client_logger(
      std::map<logger::severity,
               std::pair<std::set<std::string>, std::string>> const &streams,
      std::string log_format);

public:
  ~client_logger() override;

  client_logger(client_logger const &other);

  client_logger &operator=(client_logger const &other);

  client_logger(client_logger &&other) noexcept;

  client_logger &operator=(client_logger &&other) noexcept;

public:
  logger const *log(std::string const &message,
                    logger::severity severity) const noexcept override;

private:
  std::string format_log(std::string const &message, logger::severity severity,
                         time_t current_date_time) const;
  void cleanup_streams();
  void increment_stream_refcounts();
};

#endif // MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H
