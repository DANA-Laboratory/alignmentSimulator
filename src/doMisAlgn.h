#include "interface.h"

struct prameters
{
	public:
		float roRH;
		float roRV;
		float roNH;
		float roNV;
};
class doMisAlgn
{
	public:
		static prameters myP;
		static interface myI;
		void    misAlign(AlignValues mAlignValues,float NeqXsize,float ReqXsize,float eqZsize);
	private:
		void	misAlignVerDriven(float front,float rear,float eqXsize);
		void	misAlignVerDriver(float front,float rear,float eqXsize);
		void	misAlignHorDriver(float front,float rear,float eqXsize,float eqZsize);
		void	misAlignHorDriven(float front,float rear,float eqXsize,float eqZsize);
		void	clcAlignVerDriven(float front,float rear,float eqXsize);
		void	clcAlignVerDriver(float front,float rear,float eqXsize);
		void	clcAlignHorDriver(float front,float rear,float eqXsize,float eqZsize);
		void	clcAlignHorDriven(float front,float rear,float eqXsize,float eqZsize);
		static bool flag; 
};
