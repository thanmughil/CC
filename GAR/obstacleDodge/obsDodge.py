import pygame
import random
import tkinter as tk
from tkinter import messagebox

pygame.init()

# Screen dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Colors
WHITE = (255, 255, 255)
RED = (255, 0, 0)

# Character properties
character_width = 50
character_height = 50
character_speed = 5

# Obstacle properties
obstacle_width = 30
obstacle_height = 30
obstacle_speed = 5

# Create the game window
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Gesture Recognition Game")

clock = pygame.time.Clock()

def draw_character(x, y):
    pygame.draw.rect(screen, WHITE, (x, y, character_width, character_height))

def draw_obstacle(x, y):
    pygame.draw.rect(screen, RED, (x, y, obstacle_width, obstacle_height))

def show_game_over_popup(score):
    root = tk.Tk()
    root.withdraw()
    messagebox.showinfo("Game Over", f"Your final score: {score}")

def game_loop():
    character_x = SCREEN_WIDTH // 2 - character_width // 2
    character_y = SCREEN_HEIGHT - character_height

    obstacles = []  # List to store obstacles
    score = 0

    game_over = False

    while not game_over:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True

        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT]:
            character_x -= character_speed
            # Check left boundary
            character_x = max(character_x, 0)
        if keys[pygame.K_RIGHT]:
            character_x += character_speed
            # Check right boundary
            character_x = min(character_x, SCREEN_WIDTH - character_width)

        screen.fill((0, 0, 0))

        # Move the character
        draw_character(character_x, character_y)

        # Create new obstacles
        if random.randint(0, 100) < 5:  # Adjust the number to control obstacle frequency
            obstacle_x = random.randint(0, SCREEN_WIDTH - obstacle_width)
            obstacle_y = 0
            obstacles.append((obstacle_x, obstacle_y))

        # Move the obstacles downwards and draw them
        for i, (obstacle_x, obstacle_y) in enumerate(obstacles):
            obstacle_y += obstacle_speed
            draw_obstacle(obstacle_x, obstacle_y)
            obstacles[i] = (obstacle_x, obstacle_y)

            # Check for collision between character and obstacle
            if character_x < obstacle_x + obstacle_width and character_x + character_width > obstacle_x \
               and character_y < obstacle_y + obstacle_height and character_y + character_height > obstacle_y:
                game_over = True

            # Remove obstacles that go off the screen
            if obstacle_y > SCREEN_HEIGHT:
                obstacles.pop(i)
                score += 1

        # Display the score
        font = pygame.font.Font(None, 36)
        score_display = font.render("Score: " + str(score), True, WHITE)
        screen.blit(score_display, (10, 10))

        pygame.display.update()

        clock.tick(60)  # 60 FPS

    # Show the pop-up message box with the final score
    show_game_over_popup(score)

    pygame.quit()
    quit()

game_loop()
