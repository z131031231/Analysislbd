#include "scan.h"
#include "byte_read.h"


void PrintPageInfo(page_content* page_info)
{
	printf("page_no: %d, page_type: %d, page_lsn: %d, page_level:%d",page_info->page_no,page_info->page_type,page_info->page_lsn,page_info->page_level);
}


void ScanPageContent(char* buffer)
{
	page_content* page_info = new page_content;
	page_info->page_no = mach_read_from_4(buffer + FIL_PAGE_OFFSET);

	page_info->page_type = mach_read_from_2(buffer + FIL_PAGE_TYPE);

	page_info->page_lsn = mach_read_from_8(buffer + FIL_PAGE_LSN);

	page_info->page_level = mach_read_from_2(buffer + FIL_PAGE_OFFSET + PAGE_LEVEL);

	PrintPageInfo(page_info);

}


int ScanPage(FILE* fp,uint* page_size,ulint* pages)
{

	fseek(fp,(*page_size) * 2 , 0);
	char *buffer;
	buffer = new char[*page_size];
	for (ulint i = 3; i <= *pages; i++)
	{
		buffer = get_page_value(fp, page_size);
		ScanPageContent(buffer);

		memset(buffer,'\0',*page_size);
	}
	delete[]buffer;
	return 1;

}