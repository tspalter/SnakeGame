using System;

namespace SnakeGame
{
    public class Food
    {
        public Position Position { get; private set; }
        private Random _random = new Random();
        private int _width;
        private int _height;

        public Food(int width, int height)
        {
            _width = width;
            _height = height;
            Position = new Position(0, 0); // Initialize to a default value
            Generate();
        }

        public void Generate(Snake? snake = null)
        {
            do
            {
                Position = new Position(_random.Next(1, _width - 1), _random.Next(1, _height - 1));
            } while (snake != null && IsOnSnake(snake));
        }

        private bool IsOnSnake(Snake? snake)
        {
            if (snake == null) return false;
            foreach (var part in snake.Body)
            {
                if (part.X == Position.X && part.Y == Position.Y)
                {
                    return true;
                }
            }
            return false;
        }
    }
}
