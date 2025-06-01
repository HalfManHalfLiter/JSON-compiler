# JSON Validator

This is a simple C++ program that validates the basic syntax of a JSON file. It checks for correct bracket pairing (`{}` and `[]`), proper placement of colons (`:`) and commas (`,`), and ensures the file starts with a valid JSON structure. All messages are in English or use ASCII characters for compatibility.

## Project Structure
- `src/` - Source code:
  - `json_validator.cpp`: Main program with JSON validation logic.
- `tests/` - Example JSON files for testing:
  - `valid.json`: A valid JSON file.
  - `invalid.json`: An invalid JSON file.
- `.gitignore`: Excludes unnecessary files.
- `README.md`: This file.

## Requirements
- C++11 or later
- A C++ compiler (e.g., g++)

## How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/json-validator.git
   ```
2. Compile the program:
   ```bash
   g++ src/json_validator.cpp -o json_validator
   ```
3. Run the program:
   ```bash
   ./json_validator
   ```
4. Follow the menu instructions:
   - `h`: Display help menu.
   - `o filename`: Open and validate a JSON file (e.g., `o tests/valid.json`).
   - `c`: Validate the last opened file.
   - `q`: Quit the program.

## Example JSON Files
- **valid.json**:
```json
{
  "name": "John",
  "age": 30,
  "hobbies": ["reading", "coding"]
}
```
- **invalid.json**:
```json
{
  "name": "John",
  "age": 30,
  "hobbies": ["reading", "coding"
}
