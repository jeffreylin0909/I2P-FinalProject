#include <cstdlib>
#include <climits>
#include <algorithm>
#include <iostream>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int minimaxval(State *state, int depth,int me,int alpha,int beta){
	if (depth==0){
		return state->evaluate();
	}
	int ret;
	if (state->player==me){
		ret=INT_MIN;
		if (state->game_state==WIN){
			return INT_MAX;
		}
		for (Move M:state->legal_actions){
			alpha=ret=std::max(ret,minimaxval(state->next_state(M),depth-1,me,alpha,beta));
			if (alpha>=beta){
				break;
			}
		}
	}else {
		ret=INT_MAX;
		if (state->game_state==WIN){
			return INT_MIN;
		}
		for (Move M:state->legal_actions){
			beta=ret=std::min(ret,minimaxval(state->next_state(M),depth-1,me,alpha,beta));
			if (alpha>=beta){
				break;
			}
		}
	}
	return ret;
}
Move Submission::get_move(State *state, int depth){
	Move ret;
	if (state->legal_actions.size()){
		ret=state->legal_actions[0];
	}
	int Max=INT_MIN,tmp;
	for (Move M:state->legal_actions){
		tmp=minimaxval(state->next_state(M),depth-1,state->player,Max,INT_MAX);
		if (tmp>Max){
			ret=M;
			Max=tmp;
		}
	}
	return ret;
}
