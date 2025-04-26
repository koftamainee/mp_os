current: test-allocator-sorted-list

build:
	mkdir -p build && \
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=DEBUG -G Ninja \
	      -DCMAKE_POLICY_DEFAULT_CMP0135=NEW \
	      -DCMAKE_POLICY_VERSION_MINIMUM=3.5 .. && \
	cmake --build .

test-client-logger: build
	cd build && ./logger/client_logger/tests/mp_os_lggr_clnt_lggr_tests

test-server-logger: build
	cd build && ./logger/server_logger/tests/mp_os_lggr_srvr_lggr_tests

test-allocator-buddies: build
	cd build && ./allocator/allocator_buddies_system/tests/mp_os_allctr_allctr_bdds_sstm_tests

test-allocator-sorted-list: build
	cd build && ./allocator/allocator_sorted_list/tests/mp_os_allctr_allctr_srtd_lst_tests

test-allocator-global-heap: build
	cd build && ./allocator/allocator_global_heap/tests/mp_os_allctr_allctr_glbl_hp_tests

test-allocator-rb-tree: build
	cd build && ./allocator/allocator_red_black_tree/tests/mp_os_allctr_allctr_rb_tr_tests


test-all: test-client-logger test-server-logger \
          test-allocator-buddies test-allocator-sorted-list \
          test-allocator-global-heap test-allocator-rb-tree

test-allocators: test-allocator-buddies test-allocator-sorted-list \
                 test-allocator-global-heap test-allocator-rb-tree

test-loggers: test-client-logger test-server-logger

clean:
	rm -rf build

.PHONY: build test-all test-allocators test-loggers \
        test-client-logger test-server-logger \
        test-allocator-buddies test-allocator-sorted-list \
        test-allocator-global-heap test-allocator-rb-tree \
				clean
