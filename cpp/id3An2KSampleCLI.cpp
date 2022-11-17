/**
 * This sample shows how to perform basic face recognition tasks using id3 An2K SDK.
 */

#include <iostream>
#include "id3An2KLib.h"

void check(int err, const std::string& func_name)
{
	if (err != id3An2KError_Success)
	{
		std::cout << "Error " << err << " in " << func_name.c_str() << std::endl;
		exit(1);
	}
}

int main(int argc, char **argv)
{
	std::string data_dir = "data/";
	/**
   	 * Fill in the correct path to the license.
   	 */
	std::string license_path = "your_license_path_here";
	/**
   	 * All functions of the API return an error code.
   	 */
	int err = id3An2KError_Success;
	/**
   	 * The id3 An2K SDK needs a valid license to work.
   	 * It is required to provide a path to this license file.
   	 * It is required to call the id3An2KLicense_CheckLicense() function before calling any other function of the SDK.
   	 */
	std::cout << "Checking license" << std::endl;
	err = id3An2KLibrary_CheckLicense(license_path.c_str(), nullptr);
	check(err, "id3An2KLibrary_CheckLicense");

	/**
	 * The sample transaction file comes from NIST website and is presented as reference transaction
	 * with all record types 
	 * source: https://www.nist.gov/itl/iad/image-group/ansinist-itl-standard-references
	 */
	std::string transaction_path = data_dir + "pass-all-supported-types.an2";
	/**
	 * Transaction files can be either loaded as file or buffers
	 */
	ID3_AN2K_TRANSACTION tr;
	err = id3An2KTransaction_Initialize(&tr);
	check(err, "id3An2KTransaction_Initialize");

	err = id3An2KTransaction_FromFile(tr,transaction_path.c_str());
	check(err, "id3An2KTransaction_FromFile");

	/**
	 * Print a convenient summary of the transaction content
	 */
	char* summary = nullptr;
	int summarySize = 0;
	err = id3An2KTransaction_GetSummary(tr,summary,&summarySize);
	if(err != id3An2KError_InsufficientBuffer) { 
		check(err,"id3An2KTransaction_GetSummary_1st_call");
	}
	summary = (char*)malloc(summarySize);
	err = id3An2KTransaction_GetSummary(tr,summary,&summarySize);
	check(err,"id3An2KTransaction_GetSummary_2nd_call");
	std::cout << summary << std::endl;
	
	/**
	 * Retrieve the transaction information record
	 */
    ID3_AN2K_RECORD rec;
    err = id3An2KRecord_Initialize(&rec);
	check(err, "id3An2KRecord_Initialize");
    err = id3An2KTransaction_Get(tr, 0, rec);
	check(err, "id3An2KTransaction_Get");
	
	std::cout << "Access record n.0:" << std::endl;
	id3An2KRecordType rType;
	err = id3An2KRecord_GetRecordType(rec,&rType);
	check(err, "id3An2KRecord_GetRecordType");
	std::cout << "Record type: " << rType << std::endl;

	int fieldCount = 0;
	err = id3An2KRecord_GetCount(rec,&fieldCount);
	check(err, "id3An2KRecord_GetCount");
	std::cout << "Field count: " << fieldCount << std::endl;

	/**
	 * Fields can be accessed by three ways:
	 * - by index (from 0 to field count -1)
	 * - by field number, for example field 1.005 number is 5
	 * - by field mnemonic, for example field 1.005 mnemonic is DAT
	 */
	ID3_AN2K_FIELD field;
	err = id3An2KField_Initialize(&field);
	check(err, "id3An2KField_Initialize");
    err = id3An2KRecord_GetFieldByMnemonic(rec,"DAT",field);
	check(err, "id3An2KRecord_GetFieldByMnemonic");

	char fieldDescription[50];
	int fieldDescriptionSize = 50;
	err = id3An2KField_GetDescription(field,fieldDescription,&fieldDescriptionSize);
	check(err, "id3An2KField_GetDescription");
	std::cout << "DAT field description: " << fieldDescription << std::endl;

	/**
	 * Field data can be retrieved either as raw buffer of string, please remember that subfields are not parsed
	 * To access subfield data the user must parse the data according to the field encoding type given by the norm
	 */
	unsigned char* data_buffer = nullptr;
	int data_buffer_size = 0;
	err = id3An2KField_GetData(field,data_buffer,&data_buffer_size);
	if(err != id3An2KError_InsufficientBuffer) {
		check(err,"id3An2KField_GetData first call");
	}
	data_buffer = (unsigned char*)malloc(data_buffer_size);
	err = id3An2KField_GetData(field,data_buffer,&data_buffer_size);
	check(err,"id3An2KField_GetData second call");

	char* data_string = nullptr;
	int data_string_size = 0;
	err = id3An2KField_GetStringData(field,data_string,&data_string_size);
	if(err != id3An2KError_InsufficientBuffer) {
		check(err,"id3An2KField_GetStringData first call");
	}
	data_string = (char*)malloc(data_string_size);
	err = id3An2KField_GetStringData(field,data_string,&data_string_size);
	check(err,"id3An2KField_GetStringData second call");

	std::cout << "DAT field description: " << data_string << std::endl;

	/**
	 * Fields can of course be modified
	 */
    data_buffer[0] = '2';
    data_buffer[1] = '0';
    data_buffer[2] = '2';
    data_buffer[3] = '2';
	err = id3An2KField_SetData(field,data_buffer,data_buffer_size);
	check(err,"id3An2KField_SetData");
	/**
	 * Updated transaction can then be re-exported 
	 */
	err = id3An2KTransaction_ToFile(tr,"saved-transaction.an2");
	check(err,"id3An2KTransaction_ToFile");
    std::cout << "Saving updated transaction to ./saved-transaction.an2" << std::endl; 
	            
    /**
     * Re-opening to check
     */
	ID3_AN2K_TRANSACTION tr2;
	err = id3An2KTransaction_Initialize(&tr2);
	check(err, "id3An2KTransaction_Initialize");

	err = id3An2KTransaction_FromFile(tr2,"saved-transaction.an2");
	check(err, "id3An2KTransaction_FromFile");
	
	ID3_AN2K_RECORD rec2;
    err = id3An2KRecord_Initialize(&rec2);
	check(err, "id3An2KRecord_Initialize");
    err = id3An2KTransaction_Get(tr2, 0, rec2);
	check(err, "id3An2KTransaction_Get");

	ID3_AN2K_FIELD field2;
	err = id3An2KField_Initialize(&field2);
	check(err, "id3An2KField_Initialize");
    err = id3An2KRecord_GetFieldByMnemonic(rec2,"DAT",field2);
	check(err, "id3An2KRecord_GetFieldByMnemonic");

	char* data_string2 = nullptr;
	int data_string_size2 = 0;
	err = id3An2KField_GetStringData(field2,data_string2,&data_string_size2);
	if(err != id3An2KError_InsufficientBuffer) {
		check(err,"id3An2KField_GetStringData first call");
	}
	data_string2 = (char*)malloc(data_string_size2);
	err = id3An2KField_GetStringData(field2,data_string2,&data_string_size2);
	check(err,"id3An2KField_GetStringData second call");

	std::cout << "DAT field description re-opened: " << data_string2 << std::endl;
        
	std::cout << "End of sample" << std::endl;

	// Cleaning
	free(data_string2);
	free(data_string);
	free(data_buffer);
	free(summary);
	id3An2KField_Dispose(&field2);
	id3An2KField_Dispose(&field);
	id3An2KRecord_Dispose(&rec2);
	id3An2KRecord_Dispose(&rec);
	id3An2KTransaction_Dispose(&tr2);
	id3An2KTransaction_Dispose(&tr);
	return 0;
}
