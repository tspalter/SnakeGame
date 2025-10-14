using System;
using System.Threading;

namespace SnakeGame
{
    public class Game
    {
        private readonly int _width = 40;
        private readonly int _height = 30;
        private Snake _snake = null!;
        private Food _food = null!;
        private int _score;
        private int _highScore;
        private int _level;
        private bool _gameOver;
        private int _speed;

        public Game()
        {
        }

        public void Start()
        {
            try
            {
                Console.Title = "Snake Game";
                Console.CursorVisible = false;
                Console.SetWindowSize(_width + 2, _height + 4);
                Console.SetBufferSize(_width + 2, _height + 4);
            }
            catch (IOException)
            {
                // Console setup might fail in some environments, but we can continue.
            }

            while (true)
            {
                Setup();
                while (!_gameOver)
                {
                    HandleInput();
                    Update();
                    Draw();
                    Thread.Sleep(_speed);
                }
                ShowGameOver();
            }
        }

        private void Setup()
        {
            _snake = new Snake(_width / 2, _height / 2);
            _food = new Food(_width, _height);
            _score = 0;
            _level = 1;
            _gameOver = false;
            _speed = 150;
            Console.Clear();
        }

        private void HandleInput()
        {
            if (Console.KeyAvailable)
            {
                var key = Console.ReadKey(true).Key;
                if ((key == ConsoleKey.UpArrow || key == ConsoleKey.W) && _snake.Direction != Direction.Down)
                    _snake.Direction = Direction.Up;
                else if ((key == ConsoleKey.DownArrow || key == ConsoleKey.S) && _snake.Direction != Direction.Up)
                    _snake.Direction = Direction.Down;
                else if ((key == ConsoleKey.LeftArrow || key == ConsoleKey.A) && _snake.Direction != Direction.Right)
                    _snake.Direction = Direction.Left;
                else if ((key == ConsoleKey.RightArrow || key == ConsoleKey.D) && _snake.Direction != Direction.Left)
                    _snake.Direction = Direction.Right;
            }
        }

        private void Update()
        {
            _snake.Move();

            if (_snake.Head.X == _food.Position.X && _snake.Head.Y == _food.Position.Y)
            {
                _snake.Grow();
                _score += 10;
                _food.Generate(_snake);
            }

            if (_snake.Head.X == 0 || _snake.Head.X == _width || _snake.Head.Y == 0 || _snake.Head.Y == _height)
            {
                _gameOver = true;
            }

            for (int i = 1; i < _snake.Body.Count; i++)
            {
                if (_snake.Head.X == _snake.Body[i].X && _snake.Head.Y == _snake.Body[i].Y)
                {
                    _gameOver = true;
                }
            }

            if (_snake.Body.Count == _width * _height)
            {
                _level++;
                _speed = Math.Max(50, _speed - 20);
                _snake = new Snake(_width / 2, _height / 2);
            }
        }

        private void Draw()
        {
            Console.SetCursorPosition(0, 0);
            Console.WriteLine($"Score: {_score}  High Score: {_highScore}  Level: {_level}");

            for (int y = 0; y <= _height; y++)
            {
                for (int x = 0; x <= _width; x++)
                {
                    if (x == 0 || x == _width || y == 0 || y == _height)
                    {
                        Console.Write("#");
                    }
                    else if (_snake.Head.X == x && _snake.Head.Y == y)
                    {
                        Console.Write("O");
                    }
                    else if (IsOnSnake(x, y))
                    {
                        Console.Write("o");
                    }
                    else if (_food.Position.X == x && _food.Position.Y == y)
                    {
                        Console.Write("F");
                    }
                    else
                    {
                        Console.Write(" ");
                    }
                }
                Console.WriteLine();
            }
        }

        private bool IsOnSnake(int x, int y)
        {
            for (int i = 1; i < _snake.Body.Count; i++)
            {
                if (_snake.Body[i].X == x && _snake.Body[i].Y == y)
                {
                    return true;
                }
            }
            return false;
        }

        private void ShowGameOver()
        {
            if (_score > _highScore)
            {
                _highScore = _score;
            }
            Console.Clear();
            Console.SetCursorPosition(_width / 2 - 5, _height / 2);
            Console.WriteLine("Game Over");
            Console.SetCursorPosition(_width / 2 - 12, _height / 2 + 1);
            Console.WriteLine($"Your Score: {_score}, High Score: {_highScore}");
            Console.SetCursorPosition(_width / 2 - 10, _height / 2 + 2);
            Console.WriteLine("Press any key to play again");
            Console.ReadKey();
        }
    }
}
