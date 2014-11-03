#include <hdf5.h>
#include <string>
#include "timer.h"
#include "Poco/Path.h"

int main()
{
  Poco::Path file_path("../common/INTER00013460.nxs");
  const std::string file = file_path.toString();

  hid_t       file_id, dataset_id;  /* identifiers */
  herr_t      status;
  int         i, j, dset_data[4][6];


  /* Open an existing file. */
  file_id = H5Fopen(file.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);


  H5Gopen(file_id, "/mantid_workspace_1", H5P_DEFAULT);
  //H5Dopen(group, "CData", H5P_DEFAULT);

  /* Open an existing dataset. */
  //dataset_id = H5Dopen2(file_id, "/mantid_workspace_1", H5P_DEFAULT);
  //status = H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);

  /* Close the dataset. */
  //status = H5Dclose(dataset_id);

  /* Close the file. */
  status = H5Fclose(file_id);
  return 0;
}
