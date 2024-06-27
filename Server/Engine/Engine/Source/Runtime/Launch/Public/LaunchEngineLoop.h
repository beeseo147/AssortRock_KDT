#pragma once
#include "CoreMinimal.h"

/**
 * Implements the main engine loop.
 */
class FEngineLoop
{
public:
	/**
	 * Pre-Initialize the main loop - parse command line, sets up GIsEditor, etc..
	 *
	 * @param CmdLine The command line.
	 * @return The error level; 0 if successful, > 0 if there were errors.
	 */
	int32 PreInit(const TCHAR* CmdLine);

	/**
	 * Initialize the main loop (the rest of the initialization).
	 *
	 * @return The error level; 0 if successful, > 0 if there were errors.
	 */
	int32 Init();

	/** Advances the main loop. **/
	void Tick();
	/** Performs shut down **/
	void Exit();
};