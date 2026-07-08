# 五子棋游戏（Gomoku）— Version 2.0

一个基于终端/命令行的五子棋小游戏，支持双人对战、人机对战、悔棋、排行榜和游戏结果记录。  
本项目是自学练习作品，用 C 语言实现。

## 功能特性

- **双人对战模式**：两名玩家轮流落子，适合朋友对弈  
- **人机对战模式**：可选择作为先手（玩家 1）或后手（玩家 2），计算机使用简单的估值函数进行决策  
- **悔棋功能**：人类玩家输入 `0 0` 即可撤销上一步落子（仅限人类回合）  
- **排行榜系统**：每局结束后自动更新玩家积分（胜者 +2，平局各 +1，负者 +0），并保存在 `rankList.txt` 中  
- **游戏结果存档**：对局结果（获胜方 / 平局）及时间记录在 `result.txt` 中  
- **可调节棋盘大小**：支持 5×5 至 100×100 的棋盘  
- **直观的字符界面**：用 `X`（玩家1）和 `O`（玩家2）表示棋子
- **UTF-8 编码支持**：自动切换控制台代码页，中文显示无乱码

## 编译与运行

### 环境要求
- GCC 或任何支持 C11 标准的编译器  
- 操作系统：Windows / Linux / macOS 均可（终端需支持中文显示）

### 编译步骤
将所有 `.c` 文件一起编译，链接生成可执行文件。例如（以 `gcc` 为例）：

```bash
gcc -o main.exe main.c auto.c undo.c rank.c
```

### 运行

```bash
./main.exe
```

### 注意
- 请确保 `rankList.txt` 和 `result.txt` 与可执行文件在同一目录下，程序会自动创建/读写它们。
- 棋盘大小建议不超过 30×30，否则终端显示可能不正常，比如异常的换行
- Windows 终端下程序会自动执行 `chcp 65001` 切换到 UTF-8 编码，确保中文正常显示

## 使用说明

1. 启动程序后，首先选择游戏模式（1-双人对战，2-人机对战）  
2. 若选择人机对战，还需选择自己扮演的玩家（1-先手，2-后手）。  
3. 输入用户名（双人模式下两人各自输入；人机模式下仅人类玩家输入，另一方默认为"电脑"）
4. 设置棋盘大小（5～100）  
5. 开始游戏：
   - 人类玩家落子时，输入 **行 列**（1~棋盘大小）  
   - 输入 `0 0` 悔棋（仅限人类回合）  
   - 输入 `-1 -1` 强制退出游戏  
6. 游戏结束后，会显示获胜方 / 平局，结果自动保存并更新排行榜  
7. 赛后可选：`a` 退出，`b` 开始新对局，`c` 查看排行榜

### 人机 AI 说明
计算机使用简单的**位置评分**策略：
- 对每个空位分别计算进攻得分（己方棋子连珠价值）和防守得分（对方棋子连珠价值 ×0.8）
- 选择总分最高的位置落子。若所有位置得分为 0（空棋盘），则优先占中心  
- 连珠评分依据连子数量及是否被阻挡：
  - 五连：100000 分  
  - 活四：10000 分  
  - 冲四：1000 分  
  - 活三：100 分  
  - 眠三：10 分  
  - 活二：1 分  

该 AI 智能程度有限，只适合入门级对弈（大手子们可以轻松拿下）

## 项目文件结构

```
├── main.c            # 主程序入口，游戏流程控制
├── auto.c / auto.h   # 人机 AI 评分与自动落子
├── undo.c / undo.h   # 悔棋功能（历史栈）
├── rank.c / rank.h   # 排行榜读写与更新
├── rankList.txt      # 存储玩家积分（自动生成/更新）
├── result.txt        # 记录每局结果及时间
└── README.md         # 本文件
```

## 部分核心代码逻辑

- **胜负判定**：每次落子后，从该点沿水平、垂直、两对角线方向检查是否有连续 ≥5 个相同棋子。  
- **悔棋实现**：使用 `MoveHistory` 结构体存储每一步（行、列、玩家），`undoMove` 弹出栈顶并恢复棋盘。  
- **全局棋盘**：`board[100][100]` 以 `extern` 声明，供多个模块访问。

## 版本历史

| 版本 | 说明 |
|------|------|
| **Version 2.0** | 从 C++ 迁移至 C 语言；修复编译配置（多文件链接）；修复 Windows 终端中文乱码 |
| Version 1.2 | 添加英文 README |
| Version 1.1 | 添加 README 文档 |
| Version 1.0 | 初始版本 |

## 未来可能的改进

- 优化 AI 算法（如 alpha-beta 剪枝或蒙特卡洛方法）  
- 增加保存/载入对局功能  
- 实现图形界面（Qt 或控制台图形库）  
- 修复人机玩家对战时悔棋可能造成状态异常的边缘情况

## 许可

本项目遵循 MIT 许可协议


---

# Gomoku (Five in a Row) — Version 2.0

A terminal-based Gomoku game supporting two-player mode, human-vs-AI mode, undo, leaderboard, and game result recording.  
This project is a self-learning practice work implemented in C.

## Features

- **Two-Player Mode**: Two players take turns, perfect for playing with friends  
- **Human-vs-AI Mode**: Choose to play as first player (X) or second player (O); the AI uses a simple evaluation function for decision-making  
- **Undo Function**: Human players can enter `0 0` to undo the last move (human turn only)  
- **Leaderboard System**: Automatically updates player scores after each game (winner +2, draw +1 each, loser +0), saved in `rankList.txt`  
- **Game Result Archive**: Game results (winner / draw) and timestamps are saved in `result.txt`  
- **Adjustable Board Size**: Supports board sizes from 5×5 to 100×100  
- **Intuitive Console Interface**: Uses `X` (Player 1) and `O` (Player 2) to represent pieces
- **UTF-8 Support**: Automatically switches console code page for correct Chinese character display

## Build & Run

### Requirements
- GCC or any C11-compatible compiler  
- OS: Windows / Linux / macOS (terminal must support Chinese display)

### Build Instructions
Compile all `.c` files together. Example using `gcc`:

```bash
gcc -o main.exe main.c auto.c undo.c rank.c
```

### Run

```bash
./main.exe
```

### Notes
- Make sure `rankList.txt` and `result.txt` are in the same directory as the executable — the program will create/read them automatically.
- It is recommended to keep the board size ≤ 30×30, otherwise the terminal display may behave abnormally (e.g., unexpected line breaks).
- On Windows, the program automatically runs `chcp 65001` to switch the terminal to UTF-8 encoding.

## Usage Instructions

1. After launching, select game mode (1 - Two-Player, 2 - Human-vs-AI).  
2. If Human-vs-AI mode is selected, choose which side to play (1 - First player (X), 2 - Second player (O)).  
3. Enter usernames (both players in two-player mode; only human player in AI mode, the other defaults to "Computer").  
4. Set board size (5–100).  
5. Start the game:
   - Human players input **row column** (1~board size).  
   - Enter `0 0` to undo (human turn only).  
   - Enter `-1 -1` to force quit the game.  
6. After the game ends, the winner / draw is displayed, results are automatically saved, and the leaderboard is updated.  
7. Post-game options: `a` to exit, `b` to start a new game, `c` to view the leaderboard.

### AI Explanation

The computer uses a simple **position scoring** strategy:
- For each empty cell, calculate offensive score (value of its own pieces in a line) and defensive score (opponent's piece-line value × 0.8).  
- Select the cell with the highest total score. If all scores are 0 (empty board), prioritize the center.  
- Scoring is based on consecutive pieces and whether the ends are blocked:

| Pattern          | Score   |
|-----------------|---------|
| Five in a row   | 100,000 |
| Open four       | 10,000  |
| Blocked four    | 1,000   |
| Open three      | 100     |
| Blocked three   | 10      |
| Open two        | 1       |

This AI is relatively simple — suitable for beginner-level play.

## Project Structure

```
├── main.c            # Main program entry, game flow control
├── auto.c / auto.h   # AI scoring and auto-move logic
├── undo.c / undo.h   # Undo functionality (move history stack)
├── rank.c / rank.h   # Leaderboard reading/writing and updates
├── rankList.txt      # Stores player scores (auto-generated/updated)
├── result.txt        # Records each game result and timestamp
└── README.md         # This file
```

## Core Implementation Highlights

- **Win Detection**: After each move, checks horizontally, vertically, and along both diagonals for ≥5 consecutive same-color pieces.  
- **Undo Implementation**: Uses a `MoveHistory` structure to store each move (row, col, player); `undoMove` pops the stack and restores the board.  
- **Global Board**: `board[100][100]` declared with `extern` for access across multiple modules.

## Version History

| Version | Description |
|---------|-------------|
| **Version 2.0** | Migrated from C++ to C; fixed build config (multi-file linking); fixed Windows terminal encoding |
| Version 1.2 | Added English README |
| Version 1.1 | Added README documentation |
| Version 1.0 | Initial release |

## Possible Future Improvements

- Improve AI algorithm (e.g., alpha-beta pruning or Monte Carlo methods)  
- Add save/load game functionality  
- Implement a graphical interface (Qt or console graphics library)  
- Fix edge-case state bugs when undoing moves in Human-vs-AI mode

## License

This project is licensed under the MIT License.
