# Task 6 – Read and Print Data Correctly

| Type | Common format specifier |
|---|---|
| `int` | `%d` |
| `unsigned int` | `%u` |
| `long` | `%ld` |
| `long long` | `%lld` |
| `float` in `scanf` | `%f` |
| `double` in `scanf` | `%lf` |
| `double` in `printf` | `%f` |
| `char` | `%c` |
| string | `%s` |

Use the correct conversion specifier for the pointed-to type. A mismatch in variadic `scanf`/`printf` calls can cause undefined behaviour. `scanf` returns the number of successfully assigned fields; compare it with the expected count. For money in paise, print `paise / 100` and `paise % 100` with `%ld.%02ld`.

Alternative: read a complete line using `fgets`, then parse using `strtol` (preferred for robust error checking) or `sscanf`. Processing a line of length L takes O(L) time and a buffer of size B uses O(B) space. `fgets` makes it easier to discard an invalid line and prompt again; `scanf` can leave offending characters in the input stream unless carefully handled.
