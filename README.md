# Computer Security Capstone Projects

電腦安全課程中完成的四個實作型專案，涵蓋網路安全、系統攻擊、惡意程式設計與 CTF 漏洞利用。每個專案皆包含原始碼、說明文件與攻擊流程，展現安全技術的理解與實作能力。

---

##  Project 1：TLS Connection Hijacking

模擬中間人攻擊（MITM），攔截並解密 HTTPS 流量。透過自簽憑證建立 TLS Proxy Server，擷取帳號密碼並轉發請求至真實伺服器。

- 技術重點：TLS Proxy、封包解析、ARP Spoofing
- 語言：Python
- 概念：網路層攔截與加密通訊分析

---

##  Project 2：ICMP Redirect & DNS Spoofing

實作兩種網路欺騙技術：ICMP Redirect 攻擊與 DNS Spoofing。可操控受害者路由選擇與網域解析結果，導向攻擊者指定目標。

- 技術重點：ARP 掃描、ICMP 封包偽造、DNS 回應偽造
- 語言：C++（libtins）
- 概念：網路層與應用層欺騙

---

##  Project 3：Password Cracking & Ransomware Deployment

模擬真實攻擊者行為，從 SSH 密碼破解到勒索病毒植入。透過自動化流程上傳加密工具並加密受害者圖片，顯示勒索訊息。

- 技術重點：SSH 暴力破解、AES 加密、自解壓執行檔設計
- 語言：Python + C
- 概念：攻擊鏈建構與惡意程式設計

---

##  Project 4：Capture The Flag (CTF)

挑戰多題漏洞利用任務，包括型別溢位、PRNG 預測、邏輯錯誤、ROP、格式化字串攻擊等。每題皆與遠端伺服器互動，成功取得 flag。

- 技術重點：ROP、canary leak、GOT overwrite、格式化字串構造
- 語言：C + Python（pwntools）
- 概念：系統層漏洞分析與利用

---

##  技術總覽

- 語言：C / C++ / Python
- 工具：libtins、pwntools、OpenSSL、socket programming
- 主題：MITM、封包偽造、CTF、惡意程式、系統攻擊

---

##  學習重點

- 掌握網路與系統安全的攻擊與防禦技術
- 實作多種攻擊流程並理解其原理
- 建立結構化技術文件與作品集展示能力

---

如需詳細說明與程式碼，請參考各專案資料夾內的 `README.md` 文件。
