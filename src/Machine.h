/*
 * Machine.h
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#ifndef MACHINE_H_
#define MACHINE_H_

class Machine {
private:
	unsigned long busyUntil = 0;
public:
	/**
	 * @brief constructs a machine
	 * @return machine
	 */
	Machine() = default;
	/**
	 * @brief copyconstructs a machine
	 * @return machine
	 */
	Machine(const Machine& m);
	/**
	 * @brief gets the time until a machine is ready for another task
	 * @return timepoint
	 */
	unsigned long getBusyUntil() const;
	/**
	 * @brief sets the time until a machine is ready for another task
	 * @return timepoint
	 */
	void setBusyUntil(const unsigned long time);
	/*destructor */
	virtual ~Machine() = default;
};

#endif /* MACHINE_H_ */
