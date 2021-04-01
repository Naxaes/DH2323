#define Assert(statement, ...) _Assert(statement, #statement, __FILE__, __LINE__, __VA_ARGS__)
void _Assert(bool status, const char* statement, const char* file, unsigned line, const char* message, ...)
{
    if (status)
        return;

    static const unsigned BUFFER_SIZE = 256;
    static char buffer[BUFFER_SIZE];

    strncpy(buffer, message, BUFFER_SIZE);

    va_list argptr;
    va_start(argptr, message);
    vsnprintf(buffer, BUFFER_SIZE, message, argptr);
    va_end(argptr);

    fprintf(
        stderr,
        "[Assertion Error] (%s):\n"
        "\tFile:     %s\n"
        "\tLine:     %i\n"
        "\tMessage:  %s\n",
        statement, file, line, buffer
    );

    // Crash.
    assert(false);
}