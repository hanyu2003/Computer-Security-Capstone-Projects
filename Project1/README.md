
# CSC Project 1：TLS Connection Hijacking

## 實驗簡介

模擬中間人攻擊（MITM），透過自簽憑證攔截並解密 HTTPS 流量，分析封包內容以擷取敏感資訊（如帳號與密碼）。程式設計上結合 Python 的 socket 與 SSL 模組，建立一個 TLS Proxy Server，攔截受害者的請求並轉發至真實伺服器，同時擷取並顯示機密參數。

## 實驗任務

### Task 1：建立 TLS Proxy Server

- 使用 `ssl.SSLContext` 建立 TLS 伺服器
- 載入自簽憑證與私鑰（host.crt / host.key）
- 監聽 8080 port，等待受害者連線

### Task 2：攔截並解析 HTTPS 封包

- 接收受害者完整請求內容（含 header 與 body）
- 使用正則表達式擷取 `id` 與 `pwd` 等參數
- 解碼 URL 編碼後輸出帳號密碼資訊

### Task 3：轉發請求並回傳回應

- 解析 Host 欄位，建立與真實伺服器的 TLS 連線
- 將受害者請求轉發至目標伺服器
- 接收伺服器回應並回傳給受害者

## 環境設定（Experimental Setting）

### TLS 攻擊環境
- 攻擊者 VM 執行以下指令以重新導向 TLS 封包至 MITM 代理程式：  
```sudo ./setup.sh```
- 受害者 VM 使用以下指令啟動瀏覽器，建立 TLS 連線並接受偽造憑證：
```
google-chrome --ignore-certificate-errors --user-data-dir=/tmp/chrome_dev
chromium-browser --ignore-certificate-errors --user-data-dir=/tmp/chrome_dev
  ```  
(建議使用瀏覽器的無痕模式（Incognito Mode）進行測試。  
在真實場景中，例如 IoT 環境，若憑證未被驗證或已被注入至瀏覽器，此類攻擊可成功發動。)

### ARP Spoofing 設定
- 攻擊者 VM 在 MITM 代理程式中執行以下指令：
```
sudo arpspoof -i INTERFACE -t GATEWAY_IP CLIENT_IP
sudo arpspoof -i INTERFACE -t CLIENT_IP GATEWAY_IP
```
### 攻擊執行方式
```
sudo ./attack.py <victim_ip> <interface>
# 或自動偵測介面
sudo ./attack.py <victim_ip>
```

## 實驗觀察摘要

- 成功攔截 TLS 流量並擷取帳號密碼資訊。
- TLS Proxy Server 可穩定轉發請求與回應，模擬真實 HTTPS 行為。
- 多執行緒設計可同時處理多位受害者連線，提升效能與穩定性。
- 封包解析與 Host 判斷為關鍵步驟，需處理例外狀況（如無 Host 標頭）。
- 若搭配 ARP Spoofing，可實現完整的中間人攻擊流程。
