/**
 * @file cmp_graph_line.h
 *
 * @brief Componenets for drawing graph lines.
 *
 * @ingroup SimpleCustomPlotInternal
 *
 * @author Frans Rosencrantz
 * Contact: Frans.Rosencrantz@gmail.com
 *
 */

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "cmp_datamodels.h"
#include "cmp_internal_datamodels.h"

namespace cmp {
//==============================================================================
/**
 *  \class GraphLine
 *  \brief A templated class component to draw 2-D lines/marker symbols. This is
 *  a subcomponenet to cmp::Plot.
 *
 *  Never use this directley, always use one of the derived classes to choose
 *  the scaling.
 */
class GraphLine : public juce::Component {
 public:
  /**@breif Find closest point on graph from graph point.
   *
   * @param this_graph_point the point on the graph.
   * @param check_only_distance_from_x check the absolut distance if false else
   * only the x distance.
   * @return {closest point on graph, closest data point value}
   */
  std::pair<juce::Point<float>, juce::Point<float>> findClosestGraphPointTo(
      const juce::Point<float>& this_graph_point,
      bool check_only_distance_from_x = false) const noexcept;

  /**@breif Find closest data point to this data point.
   *
   * @param this_data_point the data point.
   * @param check_only_distance_from_x check the absolut distance if false else
   * only the x distance.
   * @return closest data point value to this_data_point.
   */
  juce::Point<float> findClosestDataPointTo(
      const juce::Point<float>& this_data_point,
      bool check_only_distance_from_x = false) const noexcept;

  /** @brief Get the colour of the graph.
   *
   *  @param graph_colour the colour of the graph
   *  @return void.
   */
  juce::Colour getColour() const noexcept;

  /** @brief Set the graph attributes.
   *
   *  @see GraphAttribute.
   *
   *  @param graph_attributes the graph_attributes.
   *  @return void.
   */
  void setGraphAttribute(const GraphAttribute& graph_attribute);

  /** @brief Set the y-values for the graph-line
   *
   *  @param y_values vector of y-values.
   *  @return void.
   */
  void setYValues(const std::vector<float>& y_values) noexcept;

  /** @brief Set the x-values for the graph-line
   *
   *  @param x_values vector of x-values.
   *  @return void.
   */
  void setXValues(const std::vector<float>& x_values) noexcept;

  /** @brief Get y-values
   *
   *  Get a const reference of the y-values.
   *
   *  @return a const reference of the y-values.
   */
  const std::vector<float>& getYValues() noexcept;

  /** @brief Get x-values
   *
   *  Get a const reference of the x-values.
   *
   *  @return a const reference of the x-values.
   */
  const std::vector<float>& getXValues() noexcept;

  /** @brief Get the graph points
   *
   *  Get a const reference of the calculated graph points.
   *
   *  @return const reference of the calculated graph points.
   */
  const GraphPoints& getGraphPoints() noexcept;

  /** @brief Set the colour of graph
   *
   *  Set the colour of graph.
   *
   *  @param graph_colour the colour of the graph
   *  @return void.
   */
  void setColour(const juce::Colour graph_colour);

  /** @brief Update the x-value in the graph points.
   *
   *  This function updates the graph points if any new parameter is set. Should
   *  be called after an parameter changed to update the graph.
   *
   *  @param common_plot_params common plot parameters.
   *  @return void.
   */
  void updateXGraphPoints(const CommonPlotParameterView common_plot_params);

  /** @brief Update the y-value in the graph points.
   *
   *  This function updates the graph points if any new parameter is set. Should
   *  be called after an parameter changed to update the graph.
   *
   *  @param common_plot_params common plot parameters.
   *  @return void.
   */
  void updateYGraphPoints(const CommonPlotParameterView common_plot_params);

  //==============================================================================
  /** @internal */
  void resized() override;
  /** @internal */
  void paint(juce::Graphics& g) override;
  /** @internal */
  void lookAndFeelChanged() override;

 private:
  /** @brief An enum to describe the state of the graph.  */
  enum class State {
    Uninitialized,
    Initialized,
  } m_state{State::Uninitialized};

  void updateYGraphPointsIntern(
      const CommonPlotParameterView common_plot_params) noexcept;
  void updateXGraphPointsIntern(
      const CommonPlotParameterView common_plot_params) noexcept;

  juce::LookAndFeel* m_lookandfeel{nullptr};

  std::vector<float> m_x_data, m_y_data;
  GraphPoints m_graph_points;
  std::vector<std::size_t> m_graph_point_indices;

  GraphAttribute m_graph_attributes;
};
}  // namespace cmp