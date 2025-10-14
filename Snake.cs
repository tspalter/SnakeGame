using System.Collections.Generic;

namespace SnakeGame
{
    public class Snake
    {
        public List<Position> Body { get; private set; }
        public Position Head => Body[0];
        public Direction Direction { get; set; }

        public Snake(int initialX, int initialY, int initialSize = 3)
        {
            Body = new List<Position>();
            for (int i = 0; i < initialSize; i++)
            {
                Body.Add(new Position(initialX - i, initialY));
            }
            Direction = Direction.Right;
        }

        public void Move()
        {
            for (int i = Body.Count - 1; i > 0; i--)
            {
                Body[i] = new Position(Body[i - 1].X, Body[i - 1].Y);
            }

            switch (Direction)
            {
                case Direction.Up:
                    Head.Y--;
                    break;
                case Direction.Down:
                    Head.Y++;
                    break;
                case Direction.Left:
                    Head.X--;
                    break;
                case Direction.Right:
                    Head.X++;
                    break;
            }
        }

        public void Grow()
        {
            Body.Add(new Position(Body[Body.Count - 1].X, Body[Body.Count - 1].Y));
        }
    }

    public enum Direction
    {
        Up,
        Down,
        Left,
        Right
    }
}
