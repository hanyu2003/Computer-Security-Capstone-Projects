# CSC Project 2：ICMP Redirect & DNS Spoofing

## 實驗簡介

模擬 Wi-Fi 網路中的中間人攻擊（MITM）與網域欺騙（Pharming）技術，透過三個階段的攻擊流程，實作封包偽造與路由操控，達到攔截並重導受害者的網路行為。程式使用 C++ 搭配 Tins 套件，操作 Ethernet/IP/ICMP/DNS 等協定，深入理解網路層與應用層的攻擊手法。

---

## 實驗任務

### Task I：Device Address Information Collection

- 掃描 Wi-Fi 網路中的所有裝置
- 擷取每台裝置的 IP 與 MAC 位址
- 建立 ARP 表並顯示裝置清單供使用者選擇
- 可使用 `/proc/net/arp` 或 raw socket 解析 ARP 封包

### Task II：ICMP Redirect 攻擊

- 偽造 ICMP Redirect 封包，欺騙受害者更新路由表
- 將 gateway 改為攻擊者，使流量先經過 MITM 節點
- 使用 RawPDU 包裝原始封包，模擬真實封包結構
- 需構造 Internet Header + 64 bits 的原始資料，並設定 checksum、identifier、sequence number 等欄位

### Task III：DNS Spoofing 攻擊

- 攔截 DNS 查詢封包，過濾目標網域（如 `www.nycu.edu.tw`）
- 偽造 DNS 回應，將查詢結果導向攻擊者指定 IP（如 `140.113.24.241`）
- 顯示 DNS 查詢與偽造回應的過程
- 可使用 Tins 套件或 NetfilterQueue 操作 DNS 封包，並記得丟棄原始查詢封包以避免重複解析


---

## 環境設定（Experimental Setting）

### ICMP Redirect 攻擊環境

- 使用者需指定目標 IP 與網路介面：
```
sudo ./icmp_redirect <target_ip> <network_interface>
```
- 程式將自動掃描區網並列出 ARP 表，供使用者選擇受害者與 gateway。
- 攻擊者將偽造 ICMP Redirect 封包，導向指定的 target IP。

### DNS Spoofing 攻擊環境
- 執行 DNS Spoofing 模組：
```
  sudo ./pharm_attack <network_interface>
```
- 程式將監聽 UDP port 53，偵測 DNS 查詢封包。
- 若查詢目標網域符合預設條件（如 `www.nycu.edu.tw`）， 則回應偽造 DNS 封包，導向攻擊者 IP（如 140.113.24.241）。

## 實驗觀察摘要
- 成功掃描區網裝置並建立 ARP 表，供使用者選擇攻擊目標。
- ICMP Redirect 可成功欺騙受害者改變路由選擇，導向非預期目標。
- DNS Spoofing 可攔截並偽造 DNS 回應，影響受害者的網域解析結果。
- 程式結構模組化，封包構建與送出流程清晰。
- 使用 Tins 套件簡化封包操作，提升開發效率與可讀性。
- 三種攻擊方式可串接使用，達成完整的中間人與網域欺騙效果。

