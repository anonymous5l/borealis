//
// Created by Anonymous on 2024/4/8.
//

#pragma once

#include <borealis.hpp>

class Chain {
  public:
    std::string text;
    std::vector<Chain> child;
};

class RecyclerCellTest
    : public brls::RecyclerCell
{
  public:
    RecyclerCellTest(std::string = "undefined");
    brls::Label* label;
    static RecyclerCellTest* create();
};

class TestDataSource
    : public brls::RecyclerDataSource
{
  public:
    int numberOfSections(brls::RecyclerFrame* recycler) override;
    int numberOfRows(brls::RecyclerFrame* recycler, int section) override;
    brls::RecyclerCell* cellForRow(brls::RecyclerFrame* recycler, brls::IndexPath index) override;
    void didSelectRowAt(brls::RecyclerFrame* recycler, brls::IndexPath indexPath) override;
    std::string titleForHeader(brls::RecyclerFrame* recycler, int section) override;
};

class RecyclingTest : public brls::Box
{
  public:
    RecyclingTest();

    static brls::View* create();

  private:
    BRLS_BIND(brls::RecyclerFrame, recycler, "recycler");
};
