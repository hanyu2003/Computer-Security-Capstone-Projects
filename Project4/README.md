# CSC Project 4：Capture The Flag (CTF)

## 專案簡介

模擬 CTF（Capture The Flag）競賽環境，透過一系列漏洞挑戰，訓練在 Linux 系統中進行程式分析、漏洞利用與逆向工程。挑戰涵蓋密碼驗證、隨機數預測、邏輯錯誤、ROP、格式化字串攻擊等技術，並以遠端伺服器互動方式取得 flag。

---

## 實驗任務

### Task I：Basic CTF Problems

#### Task I-1：Password Checker → `q1.c`
- 目標：理解 C 語言中的型別轉換與比較行為
- 題目邏輯：
  - 使用 int8_t len 儲存密碼長度，並與 0 比較。
  - 若 len < 0，則觸發 putFlag()。
- 漏洞分析：
  - strlen() 回傳 size_t（無號整數），但被儲存進 int8_t（有號整數）。
  - 當密碼長度超過 127 時，會溢位成負數，導致 len < 0 成立。
- 解法邏輯：
  - 傳送長度超過 127 的字串（例如 160 個 'a'），觸發溢位。
  - 成功進入錯誤分支並取得 flag。

#### Task I-2：Secure Random → `q2.c`
- 目標：分析 glibc 的 `rand()` 隨機數生成機制
- 題目邏輯：
  - 使用 srand(time(NULL)) 初始化隨機種子。
  - 產生 100 個 rand() 整數並進行複雜運算，回傳 r[99]。
  - 使用者輸入一個整數與結果比對。
- 漏洞分析：
  - rand() 為可預測的 PRNG，只要種子相同，結果就相同。
  - 程式執行時間與伺服器同步，即可重現結果。
- 解法邏輯：
  - 在本地模擬 long_secure_random()，使用相同時間種子。
  - 傳送計算結果給伺服器，通過驗證取得 flag。

#### Task I-3：Simple Shell → `q3`
- 目標：利用邏輯錯誤與緩衝區溢位取得 shell 權限
- 題目邏輯：
  - 提供註冊與登入功能，並根據 is_admin 判斷是否可執行指令。
  - 管理者密碼由 /dev/urandom 產生，無法預測。
  - 使用 fgets() 讀取使用者輸入，長度限制為 sizeof(struct User)（32 bytes）。
- 漏洞分析：
  - fgets() 寫入長度為 32 的 username/password，但實際結構只有 16 bytes。
  - 可透過註冊時輸入超長 username/password，覆蓋 admin.password。
- 解法邏輯：
  - 註冊時輸入 32 bytes 的密碼，覆蓋 admin 密碼。
  - 登入 admin 帳號後執行 cat flag.txt 指令，取得 flag。

#### Task I-4：Simple ROP → `q4`
- 目標：利用 ROP 技術在 NX 保護下執行 `/bin/sh`
- 題目邏輯：
  - 顯示 stack buffer 的位址，並使用 read(0, buf, 512) 讀取輸入。
  - buf 大小僅 16 bytes，存在明顯的 buffer overflow。
- 漏洞分析：
  - NX 保護啟用，無法執行 shellcode，但可使用 ROP。
  - 題目提供 gadget 位址，可構造 execve("/bin/sh", NULL, NULL) 的 ROP chain。
- 解法邏輯：
  - 根據提供的 gadget，構造 ROP payload。
  - 利用 pwntools 傳送 payload 並執行 cat flag.txt，取得 flag。

---

### Task II：Advance CTF Problems

#### Task II-1：ret2Flag → `q2_1`
- 目標：繞過 canary 並控制 return address 執行 `putflag`
- 題目邏輯：
  - 密碼由 /dev/urandom 產生，使用者有 5 次輸入機會。
  - 每次使用 read(0, buf, 64) 讀入使用者輸入，但 buf 僅 16 bytes。
- 漏洞分析：
  - 存在 stack buffer overflow，可覆蓋 canary 與 return address。
  - 題目允許多次輸入，可逐步 leak canary 與原始 return address。
- 解法邏輯：
  - 第一次輸入 25 bytes，觀察回應中是否包含 canary。
  - 第二次輸入 40 bytes，取得原始 return address。
  - 計算 putFlag() 的位址，覆蓋 return address。
  - 傳送 payload，觸發 putFlag() 執行，取得 flag。

#### Task II-2：Simple RTOS → `q2_2`
- 目標：利用格式化字串漏洞覆蓋 GOT 表
- 題目邏輯：
  - 使用者輸入指令後，程式會印出並執行 usleep()。
  - 若輸入為 exit，則觸發 should_exit = true 結束程式。
  - 使用 printf(buf) 印出使用者輸入，存在格式化字串漏洞。
- 漏洞分析：
  - sendline() 使用 printf(buf)，未加格式化，導致可注入 %n。
  - 可利用 %n 修改 exit@GOT 為 putFlag() 的位址。
- 解法邏輯：
  - 使用 fmtstr_payload() 構造格式化字串，覆蓋 GOT。
  - 傳送 exit 指令，觸發 putFlag() 執行，取得 flag。



---

## 編譯與執行方式

### 編譯 C 程式

```
make
```
### 執行各任務
```
./q1       # Task I-1
./q2       # Task I-2
./q3       # Task I-3
./q4       # Task I-4
./q2_1
./q2_2
```
