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
	Machine(unsigned long id);
	virtual ~Machine();
};

#endif /* MACHINE_H_ */
