/**
 * Author: voidrank
 * Date: 2010-11-07
 * License: CC0
 * Description: Uses the alpha-beta pruning method to find score values
 * for states in games (minimax)
 */
#pragma once

int AlphaBeta(state s, int alpha, int beta) {
	if (s.finished()) return s.score();
	for (state t : s.next()) {
		alpha = max(alpha, -AlphaBeta(t, -beta, -alpha));
		if (alpha >= beta) break;
	}
	return alpha;
}
