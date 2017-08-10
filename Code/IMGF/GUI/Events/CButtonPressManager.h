#pragma once

#include "bxcf.h"
#include "Event/Events.h"

class CButtonControl;

class CButtonPressManager : public bxcf::EventBindable<CButtonPressManager>
{
public:
	void					init(void);

private:
	void					bindEvents(void);

public:
	void					onPressButton(CButtonControl *pButton);

private:
	void					formats(void);
	void					utility(void);

	void					dat(void);
	void					img(void);
	void					itemDefinition(void);
	void					itemPlacement(void);
	void					models(void);
	void					collisions(void);
	void					textures(void);
	void					animations(void);
	void					radar(void);

	void					open(void);
	void					close(void);
	void					save(void);

	void					_import(void);
	void					_export(void);
	void					quickExport(void);
	void					rename(void);
	void					replace(void);
	void					remove(void);
	void					merge(void);
	void					split(void);
	void					convert(void);
	void					select(void);
	void					sort(void);
	void					lst(void);
};