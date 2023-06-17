#include <cstdlib>
#include <climits>
#include <algorithm>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int minimaxval(State *state, int depth,int me){
	if (depth==0){
		return state->evaluate();
	}
	int ret;
	if (state->player==me){
		ret=INT_MIN;
		for (Move M:state->legal_actions){
			ret=std::max(ret,minimaxval(state->next_state(M),depth-1,me));
		}
	}else {
		ret=INT_MAX;
		for (Move M:state->legal_actions){
			ret=std::min(ret,minimaxval(state->next_state(M),depth-1,me));
		}
	}
	return ret;
}
Move Minimax::get_move(State *state, int depth){
	Move ret;
	int Max=INT_MIN,tmp;
	for (Move M:state->legal_actions){
		tmp=minimaxval(state->next_state(M),depth-1,state->player);
		if (tmp>Max){
			ret=M;
			Max=tmp;
		}
	}
	return ret;
}
