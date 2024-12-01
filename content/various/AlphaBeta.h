/**
 * Author: voidrank
 * Date: 2010-11-07
 * License: CC0
 * Description: Uses the alpha-beta pruning method to find score values
 * for states in games (minimax). Works faster if better states are explored first.
 */
#pragma once

int AlphaBeta(State s, int alpha, int beta) {
  if (s.done()) return s.score();
  for (State t : s.next()) {
    alpha = max(alpha, -AlphaBeta(t, -beta, -alpha));
    if (alpha >= beta) break;
  }
  return alpha;
}