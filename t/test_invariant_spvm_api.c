#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Include the actual header if it exists, otherwise declare the function
// We'll use a subprocess to test the actual production code
void SPVM_build_api(const char* input, char* output, size_t output_size);

START_TEST(test_buffer_reads_never_exceed_declared_length)
{
    // Invariant: Buffer reads never exceed the declared length
    const char *payloads[] = {
        "normal_input",  // Valid input
        "A",  // Boundary: single character
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",  // 100 chars - exceeds typical buffer
        "EXPLOIT_PAYLOAD_XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",  // Exact exploit case
        ""  // Empty string
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process - run the actual function
            char output[64];  // Small buffer to test overflow
            memset(output, 0, sizeof(output));
            
            // Call the actual production function
            SPVM_build_api(payloads[i], output, sizeof(output));
            
            // If we get here without crashing, exit cleanly
            _exit(0);
        } else if (pid > 0) {
            // Parent process - check if child crashed
            int status;
            waitpid(pid, &status, 0);
            
            // Check if child terminated normally (not by signal)
            ck_assert_msg(WIFEXITED(status), 
                         "Buffer overflow detected with payload: %s", 
                         payloads[i]);
        }
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_buffer_reads_never_exceed_declared_length);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}