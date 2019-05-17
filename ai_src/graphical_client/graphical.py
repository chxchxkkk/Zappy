import os
import sys
from ai_src.client_protocol.protocol import *
from ai_src.ai.core import CoreAi

with open(os.devnull, 'w') as f:
    old_stdout = sys.stdout
    sys.stdout = f
    import pygame
    from pygame.locals import *
    sys.stdout = old_stdout


class Graphical:
    def __init__(self, port, team_name, host="localhost"):
        pygame.init()
        pygame.display.init()
        self.window = pygame.display.set_mode((1920, 1080))
        pygame.display.set_caption("Zappy client")
        self.font = pygame.font.SysFont(pygame.font.get_default_font(), 32)
        self.is_running = True
        self.ai = CoreAi(port=port, team_name=team_name, host=host)

    def run(self):
        while self.is_running:
            for event in pygame.event.get():
                self.manage_event(event)
            for action in self.ai.getElapsedActions():
                self.manage_action(action)

    def manage_event(self, event):
        if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
            self.is_running = False

    def manage_action(self, action):
        if action[0] == EVENT_CONNECTED:
            text = self.font.render('Connected', True, (255, 0, 0), (255, 255, 255))
            text_rect = text.get_rect()
            text_rect.centerx = self.window.get_rect().centerx
            text_rect.centery = self.window.get_rect().centery
            self.window.blit(text, text_rect)
            pygame.display.update()
