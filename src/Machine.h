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
	Machine() = default;
	Machine(const Machine& m);
	unsigned long getBusyUntil() const;
	void setBusyUntil(const unsigned long time);
	virtual ~Machine() = default;
};

#endif /* MACHINE_H_ */
