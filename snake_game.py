import curses
import random
import os

# High score file
HIGH_SCORE_FILE = "highscore.txt"

def load_high_score():
    """Loads the high score from the file."""
    if not os.path.exists(HIGH_SCORE_FILE):
        return 0
    with open(HIGH_SCORE_FILE, "r") as f:
        try:
            return int(f.read())
        except ValueError:
            return 0

def save_high_score(score):
    """Saves the high score to the file."""
    with open(HIGH_SCORE_FILE, "w") as f:
        f.write(str(score))

def main(stdscr):
    """Main game function."""
    # --- Initial Setup ---
    curses.curs_set(0)  # Hide the cursor
    stdscr.nodelay(1)   # Don't block for getch
    stdscr.timeout(100) # Refresh every 100ms

    # Get screen dimensions
    sh, sw = stdscr.getmaxyx()
    
    # Game board dimensions from overview
    height, width = 25, 30
    
    # Center the box
    start_y = (sh - height) // 2
    start_x = (sw - width) // 2

    # Create the game window
    win = curses.newwin(height, width, start_y, start_x)
    win.keypad(1)
    win.border(0)

    high_score = load_high_score()
    
    # --- Game Loop ---
    while True:
        win.clear() # Clear screen for new game
        score = 0
        level = 1
        speed = 150 # Initial speed (timeout in ms)

        # Initial snake and food
        snake = [[height//2, width//2], [height//2, width//2-1], [height//2, width//2-2]]
        food = [height//2, width//2+5]
        
        win.addch(food[0], food[1], '@')

        key = curses.KEY_RIGHT # Initial direction

        # --- Inner Level Loop ---
        while True:
            win.timeout(speed)
            win.border(0)
            win.addstr(0, 2, f" Score: {score} ")
            high_score_text = f"High Score: {high_score}"
            win.addstr(0, width - len(high_score_text) - 2, high_score_text)

            next_key = win.getch()
            
            # Exit game
            if next_key == 27: # ESC key
                return

            if next_key != -1:
                # Prevent snake from reversing on itself
                if (next_key == curses.KEY_LEFT and key != curses.KEY_RIGHT) or \
                   (next_key == ord('a') and key != curses.KEY_RIGHT):
                    key = curses.KEY_LEFT
                elif (next_key == curses.KEY_RIGHT and key != curses.KEY_LEFT) or \
                     (next_key == ord('d') and key != curses.KEY_LEFT):
                    key = curses.KEY_RIGHT
                elif (next_key == curses.KEY_UP and key != curses.KEY_DOWN) or \
                     (next_key == ord('w') and key != curses.KEY_DOWN):
                    key = curses.KEY_UP
                elif (next_key == curses.KEY_DOWN and key != curses.KEY_UP) or \
                     (next_key == ord('s') and key != curses.KEY_UP):
                    key = curses.KEY_DOWN
            
            # Calculate new head position
            new_head = [snake[0][0], snake[0][1]]

            if key == curses.KEY_DOWN:
                new_head[0] += 1
            if key == curses.KEY_UP:
                new_head[0] -= 1
            if key == curses.KEY_LEFT:
                new_head[1] -= 1
            if key == curses.KEY_RIGHT:
                new_head[1] += 1

            # Insert new head
            snake.insert(0, new_head)

            # --- Collision Detection ---
            # Wall collision
            if snake[0][0] == 0 or snake[0][0] == height-1 or \
               snake[0][1] == 0 or snake[0][1] == width-1:
                break # Game Over

            # Self collision
            if snake[0] in snake[1:]:
                break # Game Over

            # --- Food Handling ---
            if snake[0] == food:
                score += 10
                food = None
                while food is None:
                    nf = [
                        random.randint(1, height-2),
                        random.randint(1, width-2)
                    ]
                    food = nf if nf not in snake else None
                win.addch(food[0], food[1], '@')
            else:
                # Move snake
                tail = snake.pop()
                win.addch(tail[0], tail[1], ' ')

            # Draw snake
            win.addch(snake[0][0], snake[0][1], '#')
            
            # --- Win Condition ---
            if len(snake) == (width - 2) * (height - 2):
                level += 1
                speed = max(50, speed - 20) # Increase speed, with a max speed
                break # Break to restart loop for new level

        # --- Game Over Screen ---
        if score > high_score:
            high_score = score
            save_high_score(high_score)

        win.clear()
        win.border()
        win.addstr(height//2 - 2, (width - 10)//2, "GAME OVER")
        win.addstr(height//2, (width - len(f"Score: {score}"))//2, f"Score: {score}")
        win.addstr(height//2 + 2, (width - 22)//2, "Press any key to play again...")
        win.timeout(-1) # Wait indefinitely for next key press
        key = win.getch()
        if key == 27: # ESC
            break


if __name__ == "__main__":
    try:
        curses.wrapper(main)
    except Exception as e:
        print(f"An error occurred: {e}")
        print("If you are on Windows, make sure you have the 'windows-curses' library installed.")
