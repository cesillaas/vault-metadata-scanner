
#  Vault Metadata Scanner – C++ Security Recon Tool

A high-performance, C++17-based tool for performing **credential-less metadata exposure tests** on vault-style APIs such as 1Password, LastPass, or similar services.

This project is part of an independent security research initiative focused on **identifying publicly accessible metadata leaks** in cloud-based password management systems, following responsible disclosure standards.

---

##  Key Features

- Tests vault/item ID ranges to detect unintentionally exposed metadata  
- Parses and color-codes HTTP responses (200/403/404/429)  
- Logs time-stamped results in real time  
- Customizable scan ranges and request intervals  
- Built with `libcurl` for full control over request headers and behaviors  
- No account or login required (black-box metadata enumeration)

---

##  Why This Matters

Even if sensitive data remains protected, **unintentional exposure of metadata** can:
- Reveal internal naming conventions or structure
- Aid social engineering and phishing
- Undermine claims of “zero-knowledge” design
- Contribute to larger enumeration-based attack surfaces

This tool helps researchers safely detect such cases **before bad actors can**.

---

##  Build Instructions

### Requirements

- C++17 or higher  
- [libcurl](https://curl.se/libcurl/)  

### Build via g++

```bash
g++ src/main.cpp -o scanner -lcurl
./scanner
````

> On Windows, ensure `libcurl.dll` and `libcurl.lib` are available in your build environment or use Visual Studio with additional linker settings.

---

##  Project Structure

```
vault-metadata-scanner/
├── src/
│   └── main.cpp         # Core scanner implementation
├── .gitignore           # Ignore build artifacts and temp files
├── README.md            # You are here
├── CMakeLists.txt       # Optional CMake build support
```

---

## Example Output

```
[*] Trying: https://target.service.com/api/vaults/1002/items
[+] Possible metadata found at ID 1002 ✅
→ Partial JSON:
{
   "title": "Company Internal Vault",
   "last_updated": "2025-07-14T03:20Z",
   ...
}
[x] Not Found at ID 1003
[?] 429 Too Many Requests at ID 1004 – waiting...
```

---

##  Responsible Use

This tool is intended for:

* Educational purposes
* Ethical security research
* Responsible disclosure programs (e.g., [HackerOne](https://hackerone.com), [BugCrowd](https://bugcrowd.com))
* Exploring public metadata exposure **without attempting to bypass authentication**

**Do not** use this tool against any target without prior permission or participation in a legal disclosure program.



