

#  vault-metadata-scanner

A high-performance, C++-based tool to brute-force test metadata access in vault-style APIs such as **1Password**, **LastPass**, or other zero-knowledge cloud password managers — **without authentication**.

This tool is part of an independent security research project aimed at identifying real-world unsafe metadata exposure vectors within credential vault systems.

---

##  Features

-  Bruteforces vault/item ID patterns with live response parsing  
-  Simulates unauthenticated attackers (no login required)  
-  Parses HTTP responses (200/403/404/429) and JSON metadata  
-  Terminal logging with color and timestamp  
-  Customizable scan range and sleep timer  
-  No API key or user credentials needed (blackbox scan)

---

##  File Structure

```

vault-metadata-scanner/
├── src/
│   └── main.cpp          # Full source code
├── CMakeLists.txt        # For optional CMake support
├── README.md             # You are here
├── .gitignore            # Ignores binaries, build dirs, temp files

````

---

## 🔧 Build Instructions

### Requirements

- C++17 or higher  
- [libcurl](https://curl.se/libcurl/) (Windows users: see [curl.se/windows](https://curl.se/windows))

### Build via g++

```bash
g++ src/main.cpp -o scanner -lcurl
./scanner
````

> On Windows, ensure `libcurl.dll` and `libcurl.lib` are available in your build path or linked via Visual Studio.

---

##  Example Output

```
[*] Trying: https://start.1password.com/api/v1/vaults/1002/items
[+] FOUND at ID 1002 ✅
→ Response (first 300 chars):
{
    "title": "Internal Dev Vault",
    "created_at": "2025-07-14T10:33Z",
    ...
}
[x] Not Found at ID 1003
[?] Code 429 (Rate Limited) at ID 1004
```

---

##  Ethical Use

This repository was created for **educational purposes and responsible security research** only.
If you discover a vulnerability using this tool, please report it through coordinated disclosure channels like:

* [HackerOne](https://hackerone.com/)
* [BugCrowd](https://bugcrowd.com/)
* [1Password's Disclosure Policy](https://hackerone.com/1password)

---

