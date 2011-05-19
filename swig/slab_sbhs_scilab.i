/* -*- c++ -*- */

GR_SWIG_BLOCK_MAGIC(slab,sbhs_scilab);

slab_sbhs_scilab_sptr slab_make_sbhs_scilab (char* filename,int fan_speed,int heater_temperature);

class slab_sbhs_scilab : public gr_block
{
private:
  
  friend slab_sbhs_scilab_sptr slab_make_sbhs_scilab (char* filename,int fan_speed,int heater_temperature);  

  slab_sbhs_scilab (char* filename,int fan_speed,int heater_temperature);
  char filename[100];

 ~slab_sbhs_scilab ();

public:

  float get_scilab(char *var);
  int d_fan_speed;
  int d_heater_temperature;
  void python_sleep();
  void set_fan_speed(int fan_speed);
  void set_heater_temperature(int heater_temperature);
  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);

 };

