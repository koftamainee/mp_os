cmake_minimum_required(VERSION 3.21)
project(mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr)

add_subdirectory(tests)
add_library(
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr
        include/splay_tree.h)
target_include_directories(
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr
        PUBLIC
        ./include)
target_link_libraries(
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr
        PUBLIC
        mp_os_cmmn)
target_link_libraries(
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr
        PUBLIC
        mp_os_lggr_lggr)
target_link_libraries(
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr
        PUBLIC
        mp_os_allctr_allctr)
target_link_libraries(
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr
        PUBLIC
        mp_os_assctv_cntnr)
target_link_libraries(
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr
        PUBLIC
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr)
set_target_properties(
        mp_os_assctv_cntnr_srch_tr_bnr_srch_tr_spl_tr PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "splay tree implementation library")
