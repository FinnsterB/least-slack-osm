/*
 * Machine.h
 *
 *  Created on: 24 feb. 2023
 *      Author: marcv
 */

#ifndef MACHINE_H_
#define MACHINE_H_

class Machine
{
public:
	int id;
	unsigned long timeBusy;
	Machine(unsigned long id);
	virtual ~Machine();
	bool operator<(const Machine& rhs);
	unsigned long
	getTimeBusy() const;
	void
	setTimeBusy(unsigned long timeBusy);
};

#endif /* MACHINE_H_ */