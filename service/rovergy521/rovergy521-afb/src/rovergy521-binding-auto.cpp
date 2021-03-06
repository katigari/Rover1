/* Copyright 2018 Pedro Cuadra - pjcuadra@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* WARNING: This file is automatically generated by raml2agl */
extern "C"
{
   #define AFB_BINDING_VERSION 2
   #include <afb/afb-binding.h>
};


#include <cstddef>
#include <cstdio>
#include <cstring>

#include <json-c/json.h>

#include <service/ServiceRoverGy521.h>
// #include <all_types.h>

static ServiceRoverGy521 obj;

static int init()
{
  int rc = 0;
	AFB_NOTICE("Initializing... ");
  rc = obj.init();
	AFB_NOTICE("Initialization done!");
	return rc;
}

static void read_acc_y(struct afb_req request) {
  json_object *args = afb_req_json(request);
  int _var_acc_y = static_cast<int>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_acc_y");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_acc_y(_var_acc_y);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_acc_y' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_acc_y' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_int(_var_acc_y);
  json_object_object_add(new_json, "acc_y", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}

static void read_acc_x(struct afb_req request) {
  json_object *args = afb_req_json(request);
  int _var_acc_x = static_cast<int>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_acc_x");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_acc_x(_var_acc_x);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_acc_x' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_acc_x' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_int(_var_acc_x);
  json_object_object_add(new_json, "acc_x", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}

static void read_acc_z(struct afb_req request) {
  json_object *args = afb_req_json(request);
  int _var_acc_z = static_cast<int>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_acc_z");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_acc_z(_var_acc_z);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_acc_z' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_acc_z' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_int(_var_acc_z);
  json_object_object_add(new_json, "acc_z", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}

static void read_gyro_x(struct afb_req request) {
  json_object *args = afb_req_json(request);
  int _var_gyro_x = static_cast<int>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_gyro_x");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_gyro_x(_var_gyro_x);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_gyro_x' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_gyro_x' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_int(_var_gyro_x);
  json_object_object_add(new_json, "gyro_x", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}

static void read_gyro_y(struct afb_req request) {
  json_object *args = afb_req_json(request);
  int _var_gyro_y = static_cast<int>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_gyro_y");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_gyro_y(_var_gyro_y);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_gyro_y' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_gyro_y' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_int(_var_gyro_y);
  json_object_object_add(new_json, "gyro_y", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}

static void read_gyro_z(struct afb_req request) {
  json_object *args = afb_req_json(request);
  int _var_gyro_z = static_cast<int>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_gyro_z");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_gyro_z(_var_gyro_z);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_gyro_z' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_gyro_z' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_int(_var_gyro_z);
  json_object_object_add(new_json, "gyro_z", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}

static void read_angle_y(struct afb_req request) {
  json_object *args = afb_req_json(request);
  double _var_angle_y = static_cast<double>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_angle_y");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_angle_y(_var_angle_y);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_angle_y' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_angle_y' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_double(_var_angle_y);
  json_object_object_add(new_json, "angle_y", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}

static void read_angle_x(struct afb_req request) {
  json_object *args = afb_req_json(request);
  double _var_angle_x = static_cast<double>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_angle_x");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_angle_x(_var_angle_x);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_angle_x' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_angle_x' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_double(_var_angle_x);
  json_object_object_add(new_json, "angle_x", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}

static void read_angle_z(struct afb_req request) {
  json_object *args = afb_req_json(request);
  double _var_angle_z = static_cast<double>(0);
  json_object * new_json = json_object_new_object();
  json_object * new_sub_json = NULL;
  int ret = 0;

  AFB_NOTICE("[rovergy521] Calling read_angle_z");


  if (args) {
    // Parse args if possible


  }


  ret = obj.read_angle_z(_var_angle_z);
  if (ret) {
    AFB_ERROR("[rovergy521] Verb 'read_angle_z' returning error");
    afb_req_fail_f(request, "bad-request", "Verb 'read_angle_z' returning error %d", ret);
    return;
  }


  new_sub_json = json_object_new_double(_var_angle_z);
  json_object_object_add(new_json, "angle_z", new_sub_json);

  afb_req_success(request, new_json, NULL);
  // Release the request json object
  json_object_put(new_json);

}


// static const struct afb_auth _afb_auths_v2_monitor[] = {
// 	{type : afb_auth_Permission, text : "urn:AGL:permission:monitor:public:set"},
// 	{type : afb_auth_Permission, text : "urn:AGL:permission:monitor:public:get"},
// 	{type : afb_auth_Or, first : &_afb_auths_v2_monitor[1], next : &_afb_auths_v2_monitor[0]}
// };

static const struct afb_verb_v2 verbs[] = {
  /*Without security*/
  {.verb = "read_acc_y", .callback = read_acc_y, .auth = NULL, .info = "Read Acceleration Y", .session = 0},
  {.verb = "read_acc_x", .callback = read_acc_x, .auth = NULL, .info = "Read Acceleration X", .session = 0},
  {.verb = "read_acc_z", .callback = read_acc_z, .auth = NULL, .info = "Read Acceleration Z", .session = 0},
  {.verb = "read_gyro_x", .callback = read_gyro_x, .auth = NULL, .info = "Read Gyro X", .session = 0},
  {.verb = "read_gyro_y", .callback = read_gyro_y, .auth = NULL, .info = "Read Gyro Y", .session = 0},
  {.verb = "read_gyro_z", .callback = read_gyro_z, .auth = NULL, .info = "Read Gyro Z", .session = 0},
  {.verb = "read_angle_y", .callback = read_angle_y, .auth = NULL, .info = "Read Angle Y", .session = 0},
  {.verb = "read_angle_x", .callback = read_angle_x, .auth = NULL, .info = "Read Angle X", .session = 0},
  {.verb = "read_angle_z", .callback = read_angle_z, .auth = NULL, .info = "Read Angle Z", .session = 0},
  {.verb= NULL, .callback=NULL, .auth = NULL, .info = NULL, .session = 0 }
};

const struct afb_binding_v2 afbBindingV2 = {
  .api = "rovergy521",
  .specification = "",
  .info = "Auto generated - Rover Gy521",
  .verbs = verbs,
  .preinit = NULL,
  .init = init,
  .onevent = NULL,
  .noconcurrency = 1
};