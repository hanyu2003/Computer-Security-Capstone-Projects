# CSC Project 3：Password Cracking & Ransomware Deployment

## 實驗簡介

模擬真實攻擊者入侵流程，從密碼破解、勒索病毒植入到遠端控制執行，完整呈現攻擊鏈的自動化與技術細節。程式設計結合 Python 與 C，涵蓋 SSH 暴力破解、AES 加密工具部署、惡意程式壓縮與執行等技術，並透過攻擊伺服器提供病毒與訊息下載功能。

---

## 實驗任務

### Task I：密碼破解與登入

- 使用 `victim.dat` 中的單字組合產生所有可能密碼
- 嘗試使用 SSH 登入受害者主機（帳號：`csc2025`）
- 成功登入後立即停止攻擊並進行後續植入
- 加入 retry 機制處理連線失敗與例外狀況

### Task II：勒索病毒植入與執行

- 將 `/usr/bin/echo` 壓縮為 `echo.gz` 並轉換為 C 陣列（`echo_gz.h`）
- 編譯 `echo.c`，嵌入壓縮病毒並加入 SHA3-512 簽章
- 上傳至受害者 `/app/echo` 並設定執行權限
- 執行後會：
  - 下載 AES 加密工具與勒索訊息
  - 加密 `/app/Pictures/` 中所有 `.jpg` 檔案
  - 顯示勒索訊息（banner）
  - 解壓並執行原始 echo 指令

### Task III：攻擊伺服器建置

- 使用 Python 建立 TCP socket server
- 提供 `aes-tool` 與 `banner` 下載功能
- 根據受害者請求傳送對應檔案
- 顯示連線來源與傳送紀錄


---

## 執行方式

### 編譯 echo.c 與 aes-tool

```
make
```
### 啟動攻擊伺服器
```
./attack_server.py <Attacker port>
```
### 執行密碼破解與植入攻擊
```
./crack_attack.py <Victim IP> <Attacker IP> <Attacker port>
```

---
## 實驗觀察摘要
- 密碼組合使用 permutation，涵蓋所有可能順序與長度，成功登入後立即停止攻擊。
- echo.c 透過 gzip 壓縮與 xxd 轉換，實現病毒壓縮與嵌入，並使用 OpenSSL 加簽。
- 加密流程使用 AES 工具加密圖片並覆蓋原始檔案，達到勒索效果。
- 攻擊伺服器可穩定提供檔案下載，支援多連線並記錄請求來源。
- 整體流程自動化程度高，模擬真實攻擊者行為，具備技術深度與完整性。
