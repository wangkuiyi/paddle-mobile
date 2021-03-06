/* Copyright (c) 2016 Baidu, Inc. All Rights Reserved.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
==============================================================================*/

#pragma once

#include <string>
#include "common/log.h"
#include "common/type_define.h"
#include "framework/lod_tensor.h"
#include "framework/scope.h"
#include "framework/tensor.h"
#include "framework/variable.h"

namespace paddle_mobile {
namespace operators {

using namespace framework;

class OpParam : PaddleMobileObject {
 public:
 protected:
  template <typename T>
  static T *InputFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Input", inputs, scope);
  }

  template <typename T>
  static T *InputXFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("X", inputs, scope);
  }

  template <typename T>
  static T *InputYFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Y", inputs, scope);
  }

  template <typename T>
  static T *InputBiasFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Bias", inputs, scope);
  }
  template <typename T>
  static T *InputVarianceFrom(const VariableNameMap &inputs,
                              const Scope &scope) {
    return GetVarValue<T>("Variance", inputs, scope);
  }
  template <typename T>
  static T *InputMeanFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Mean", inputs, scope);
  }
  template <typename T>
  static T *InputScaleFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Scale", inputs, scope);
  }
  template <typename T>
  static T *InputImageFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Image", inputs, scope);
  }
  template <typename T>
  static T *InputPriorBoxFrom(const VariableNameMap &inputs,
                              const Scope &scope) {
    return GetVarValue<T>("PriorBox", inputs, scope);
  }
  template <typename T>
  static T *InputPriorBoxVarFrom(const VariableNameMap &inputs,
                                 const Scope &scope) {
    return GetVarValue<T>("PriorBoxVar", inputs, scope);
  }
  // LoDTensor but now use Tensor
  template <typename T>
  static T *InputTargetBoxFrom(const VariableNameMap &inputs,
                               const Scope &scope) {
    return GetVarValue<T>("TargetBox", inputs, scope);
  }

  template <typename T>
  static std::vector<T *> InputMultiFrom(const VariableNameMap &inputs,
                                         const Scope &scope) {
    return GetMultiVarValue<T>("X", inputs, scope);
  }

  template <typename T>
  static T *OutputFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("Output", outputs, scope);
  }

  template <typename T>
  static T *OutFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("Out", outputs, scope);
  }

  template <typename T>
  static T *OutputYFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("Y", outputs, scope);
  }

  template <typename T>
  static T *OutputBoxesFrom(const VariableNameMap &outputs,
                            const Scope &scope) {
    return GetVarValue<T>("Boxes", outputs, scope);
  }

  template <typename T>
  static T *OutputBoxFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("OutputBox", outputs, scope);
  }

  template <typename T>
  static T *OutputVariancesFrom(const VariableNameMap &outputs,
                                const Scope &scope) {
    return GetVarValue<T>("Variances", outputs, scope);
  }

  template <typename T>
  static T *MidOutFrom(const VariableNameMap &outputs, const Scope &scope) {
    return GetVarValue<T>("MidOut", outputs, scope);
  }

  template <typename T>
  static T *FilterFrom(const VariableNameMap &inputs, const Scope &scope) {
    return GetVarValue<T>("Filter", inputs, scope);
  }

  template <typename T>
  static const T GetAttr(const std::string &key, const AttributeMap &map) {
    return ((Attribute)map.at(key)).Get<T>();
  }

  template <typename T>
  static T *GetVarValue(const std::string &key, const VariableNameMap &var_map,
                        const Scope &scope) {
    auto var_vec = var_map.at(key);
    if (!var_vec.empty()) {
      //      std::cout << " get var value -- " << var_vec[0] <<
      //      std::endl;
      auto var = scope.FindVar(var_vec[0]);
      return var->GetMutable<T>();
    } else {
      return nullptr;
    }
  }

  template <typename T>
  static std::vector<T *> GetMultiVarValue(const std::string &key,
                                           const VariableNameMap &var_map,
                                           const Scope &scope) {
    auto var_vecs = var_map.at(key);
    assert(var_vecs.size() > 1);
    std::vector<T *> var_res;
    for (auto &var_vec : var_vecs) {
      auto var = scope.FindVar(var_vec);
      var_res.push_back(var->GetMutable<T>());
    }
    return var_res;
  }
};

class ConvParam : OpParam {
 public:
  ConvParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const framework::AttributeMap &attrs,
            const framework::Scope &scope) {
    filter_ = FilterFrom<framework::LoDTensor>(inputs, scope);
    input_ = InputFrom<framework::Tensor>(inputs, scope);
    output_ = OutputFrom<framework::Tensor>(outputs, scope);
    strides_ = GetAttr<std::vector<int>>("strides", attrs);
    paddings_ = GetAttr<std::vector<int>>("paddings", attrs);
    dilations_ = GetAttr<std::vector<int>>("dilations", attrs);
    groups = GetAttr<int>("groups", attrs);
  }

  const Tensor *Input() const { return input_; }

  const LoDTensor *Filter() const { return filter_; }

  Tensor *Output() const { return output_; }

  const std::vector<int> &Strides() const { return strides_; }

  const std::vector<int> &Paddings() const { return paddings_; }

  const std::vector<int> &Dilations() const { return dilations_; }

  const int &Groups() const { return groups; }

 private:
  Tensor *input_;
  Tensor *output_;
  LoDTensor *filter_;
  std::vector<int> strides_;
  std::vector<int> paddings_;
  std::vector<int> dilations_;
  int groups;
};

Print &operator<<(Print &printer, const ConvParam &conv_param);

class ElementwiseAddParam : OpParam {
 public:
  ElementwiseAddParam(const VariableNameMap &inputs,
                      const VariableNameMap &outputs,
                      const framework::AttributeMap &attrs,
                      const framework::Scope &scope) {
    input_x_ = InputXFrom<framework::Tensor>(inputs, scope);
    input_y_ = InputYFrom<framework::Tensor>(inputs, scope);
    out_ = OutFrom<framework::Tensor>(outputs, scope);
    axis_ = GetAttr<int>("axis", attrs);
  }

  const Tensor *InputX() const { return input_x_; }

  const Tensor *InputY() const { return input_y_; }

  Tensor *Out() const { return out_; }

  const int &Axis() const { return axis_; }

 private:
  Tensor *input_x_;
  Tensor *input_y_;
  Tensor *out_;
  int axis_;
};

class MulParam : OpParam {
 public:
  MulParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
           const framework::AttributeMap &attrs,
           const framework::Scope &scope) {
    input_x_ = InputXFrom<framework::Tensor>(inputs, scope);
    input_y_ = InputYFrom<framework::Tensor>(inputs, scope);
    out_ = OutFrom<framework::Tensor>(outputs, scope);
    x_num_col_dims_ = GetAttr<int>("x_num_col_dims", attrs);
    y_num_col_dims_ = GetAttr<int>("y_num_col_dims", attrs);
  }

  const Tensor *InputX() const { return input_x_; }

  const Tensor *InputY() const { return input_y_; }

  Tensor *Out() const { return out_; }

  const int &XNumColDims() const { return x_num_col_dims_; }

  const int &YNumColDims() const { return y_num_col_dims_; }

 private:
  Tensor *input_x_;
  Tensor *input_y_;
  Tensor *out_;
  int x_num_col_dims_;
  int y_num_col_dims_;
};

class ConcatParam : public OpParam {
 public:
  ConcatParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
              const framework::AttributeMap &attrs,
              const framework::Scope &scope) {
    inputs_ = InputMultiFrom<framework::Tensor>(inputs, scope);
    out_ = OutFrom<framework::Tensor>(outputs, scope);
    axis_ = GetAttr<int>("axis", attrs);
  }

  std::vector<Tensor *> Inputs() const { return inputs_; }

  Tensor *Out() const { return out_; }

  const int &Axis() const { return axis_; }

 private:
  std::vector<Tensor *> inputs_;
  Tensor *out_;
  int axis_;
};

class LrnParam : public OpParam {
 public:
  LrnParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
           const framework::AttributeMap &attrs,
           const framework::Scope &scope) {
    input_x_ = InputXFrom<framework::Tensor>(inputs, scope);
    out_ = OutFrom<framework::Tensor>(outputs, scope);
    mid_out_ = MidOutFrom<framework::Tensor>(outputs, scope);
    n_ = GetAttr<int>("n", attrs);
    alpha_ = GetAttr<float>("alpha", attrs);
    beta_ = GetAttr<float>("beta", attrs);
    k_ = GetAttr<float>("k", attrs);
    data_format_ = GetAttr<std::string>("data_format", attrs);
  }

  const Tensor *InputX() const { return input_x_; }

  Tensor *Out() const { return out_; }

  Tensor *MidOut() const { return mid_out_; }

  const int &N() const { return n_; }

  const float &Alpha() const { return alpha_; }

  const float &Beta() const { return beta_; }

  const float &K() const { return k_; }

  const std::string &DataFormat() const { return data_format_; }

 private:
  Tensor *input_x_;
  Tensor *out_;
  Tensor *mid_out_;
  int n_;
  float alpha_;
  float beta_;
  float k_;
  std::string data_format_;
};
class BatchNormParam : OpParam {
 public:
  BatchNormParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                 const framework::AttributeMap &attrs,
                 const framework::Scope &scope) {
    input_x_ = InputXFrom<framework::Tensor>(inputs, scope);
    output_y_ = OutputYFrom<framework::Tensor>(outputs, scope);
    input_bias_ = InputBiasFrom<framework::Tensor>(inputs, scope);
    input_mean_ = InputMeanFrom<framework::Tensor>(inputs, scope);
    input_scale_ = InputScaleFrom<framework::Tensor>(inputs, scope);
    input_variance_ = InputVarianceFrom<framework::Tensor>(inputs, scope);
    epsilon_ = GetAttr<float>("epsilon", attrs);
    momentum_ = GetAttr<float>("momentum", attrs);
    is_test_ = GetAttr<bool>("is_test", attrs);
  }

  const Tensor *InputX() const { return input_x_; }

  Tensor *OutputY() const { return output_y_; }

  const Tensor *InputBias() const { return input_bias_; }

  const Tensor *InputMean() const { return input_mean_; }

  const Tensor *InputScale() const { return input_scale_; }

  const Tensor *InputVariance() const { return input_variance_; }

  const float &Epsilon() const { return epsilon_; }

  const float &Momentum() const { return momentum_; }

  const bool &IsTest() const { return is_test_; }

  const std::string &DataFormat() const { return data_format_; }

 private:
  Tensor *input_x_;
  Tensor *output_y_;
  Tensor *input_bias_;
  Tensor *input_mean_;
  Tensor *input_scale_;
  Tensor *input_variance_;
  float epsilon_;
  float momentum_;
  bool is_test_;
  std::string data_format_;
};
class PoolParam : public OpParam {
 public:
  PoolParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
            const framework::AttributeMap &attrs,
            const framework::Scope &scope) {
    input_ = InputXFrom<framework::Tensor>(inputs, scope);

    output_ = OutFrom<framework::Tensor>(outputs, scope);
    pooling_type_ = GetAttr<std::string>("pooling_type", attrs);
    ksize_ = GetAttr<std::vector<int>>("ksize", attrs);
    strides_ = GetAttr<std::vector<int>>("strides", attrs);
    paddings_ = GetAttr<std::vector<int>>("paddings", attrs);
    ceil_mode_ = GetAttr<bool>("ceil_mode", attrs);
    gloabal_pooling_ = GetAttr<bool>("global_pooling", attrs);
  }

  const Tensor *Input() const { return input_; }

  Tensor *Output() const { return output_; }

  const std::string &PoolingType() const { return pooling_type_; }

  const std::vector<int> &Ksize() const { return ksize_; }

  const std::vector<int> &Strides() const { return strides_; }

  const std::vector<int> &Paddings() const { return paddings_; }

  bool isCeilMode() const { return ceil_mode_; }

  bool isGlobalPooling() const { return gloabal_pooling_; }

 private:
  Tensor *input_;
  Tensor *output_;
  std::string pooling_type_;
  std::vector<int> ksize_;
  std::vector<int> strides_;
  std::vector<int> paddings_;
  bool ceil_mode_;
  bool gloabal_pooling_ = false;
};

class PriorBoxParam : public OpParam {
 public:
  PriorBoxParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const framework::AttributeMap &attrs,
                const framework::Scope &scope) {
    input_ = InputFrom<framework::Tensor>(inputs, scope);
    input_image_ = InputImageFrom<framework::Tensor>(inputs, scope);
    output_boxes_ = OutputBoxesFrom<framework::Tensor>(outputs, scope);
    output_variances_ = OutputVariancesFrom<framework::Tensor>(outputs, scope);
    min_sizes_ = GetAttr<std::vector<float>>("min_sizes", attrs);
    max_sizes_ = GetAttr<std::vector<float>>("max_sizes", attrs);
    aspect_ratios_ = GetAttr<std::vector<float>>("aspect_ratios", attrs);
    variances_ = GetAttr<std::vector<float>>("variances", attrs);
    flip_ = GetAttr<bool>("flip", attrs);
    clip_ = GetAttr<bool>("clip", attrs);
    step_w_ = GetAttr<float>("step_w", attrs);
    step_h_ = GetAttr<float>("step_h", attrs);
    offset_ = GetAttr<float>("offset", attrs);
  }
  const Tensor *Input() const { return input_; }

  const Tensor *InputImage() const { return input_image_; }

  Tensor *OutputBoxes() const { return output_boxes_; }

  Tensor *OutputVariances() const { return output_variances_; }

  const std::vector<float> &MinSizes() const { return min_sizes_; }

  const std::vector<float> &MaxSizes() const { return max_sizes_; }

  const std::vector<float> &AspectRatios() const { return aspect_ratios_; }

  const std::vector<float> &Variances() const { return variances_; }

  const bool &Flip() const { return flip_; }

  const bool &Clip() const { return clip_; }

  const float &StepW() const { return step_w_; }

  const float &StepH() const { return step_h_; }

  const float &Offset() const { return offset_; }

 private:
  Tensor *input_;
  Tensor *input_image_;
  Tensor *output_boxes_;
  Tensor *output_variances_;
  std::vector<float> min_sizes_;
  std::vector<float> max_sizes_;
  std::vector<float> aspect_ratios_;
  std::vector<float> variances_;
  bool flip_;
  bool clip_;
  float step_w_;
  float step_h_;
  float offset_;
};

class BoxCoderParam : public OpParam {
 public:
  BoxCoderParam(const VariableNameMap &inputs, const VariableNameMap &outputs,
                const framework::AttributeMap &attrs,
                const framework::Scope &scope) {
    input_priorbox_ = InputPriorBoxFrom<framework::Tensor>(inputs, scope);
    input_priorboxvar_ = InputPriorBoxVarFrom<framework::Tensor>(inputs, scope);
    input_targetbox_ = InputTargetBoxFrom<framework::Tensor>(inputs, scope);
    output_box_ = OutputBoxFrom<framework::Tensor>(outputs, scope);
    code_type_ = GetAttr<std::string>("code_type", attrs);
  }
  const Tensor *InputPriorBox() const { return input_priorbox_; }

  const Tensor *InputPriorBoxVar() const { return input_priorboxvar_; }

  const Tensor *InputTargetBox() const { return input_targetbox_; }

  Tensor *OutputBox() const { return output_box_; }

  const std::string &CodeType() const { return code_type_; }

 private:
  Tensor *input_priorbox_;
  Tensor *input_priorboxvar_;
  Tensor *input_targetbox_;
  Tensor *output_box_;
  std::string code_type_;
};
}  // namespace operators
}  // namespace paddle_mobile
