package DataCommon {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.RewardItemCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class CommonBaseRewardCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.food", "food", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var food$field:DataCommon.RewardItemCPP;

		public function clearFood():void {
			food$field = null;
		}

		public function get hasFood():Boolean {
			return food$field != null;
		}

		public function set food(value:DataCommon.RewardItemCPP):void {
			food$field = value;
		}

		public function get food():DataCommon.RewardItemCPP {
			return food$field;
		}

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.iron", "iron", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var iron$field:DataCommon.RewardItemCPP;

		public function clearIron():void {
			iron$field = null;
		}

		public function get hasIron():Boolean {
			return iron$field != null;
		}

		public function set iron(value:DataCommon.RewardItemCPP):void {
			iron$field = value;
		}

		public function get iron():DataCommon.RewardItemCPP {
			return iron$field;
		}

		/**
		 *  @private
		 */
		public static const ORDER:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.order", "order", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var order$field:DataCommon.RewardItemCPP;

		public function clearOrder():void {
			order$field = null;
		}

		public function get hasOrder():Boolean {
			return order$field != null;
		}

		public function set order(value:DataCommon.RewardItemCPP):void {
			order$field = value;
		}

		public function get order():DataCommon.RewardItemCPP {
			return order$field;
		}

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.exp", "exp", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var exp$field:DataCommon.RewardItemCPP;

		public function clearExp():void {
			exp$field = null;
		}

		public function get hasExp():Boolean {
			return exp$field != null;
		}

		public function set exp(value:DataCommon.RewardItemCPP):void {
			exp$field = value;
		}

		public function get exp():DataCommon.RewardItemCPP {
			return exp$field;
		}

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.coin", "coin", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var coin$field:DataCommon.RewardItemCPP;

		public function clearCoin():void {
			coin$field = null;
		}

		public function get hasCoin():Boolean {
			return coin$field != null;
		}

		public function set coin(value:DataCommon.RewardItemCPP):void {
			coin$field = value;
		}

		public function get coin():DataCommon.RewardItemCPP {
			return coin$field;
		}

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.wood", "wood", (6 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var wood$field:DataCommon.RewardItemCPP;

		public function clearWood():void {
			wood$field = null;
		}

		public function get hasWood():Boolean {
			return wood$field != null;
		}

		public function set wood(value:DataCommon.RewardItemCPP):void {
			wood$field = value;
		}

		public function get wood():DataCommon.RewardItemCPP {
			return wood$field;
		}

		/**
		 *  @private
		 */
		public static const HAMMER:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.hammer", "hammer", (7 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var hammer$field:DataCommon.RewardItemCPP;

		public function clearHammer():void {
			hammer$field = null;
		}

		public function get hasHammer():Boolean {
			return hammer$field != null;
		}

		public function set hammer(value:DataCommon.RewardItemCPP):void {
			hammer$field = value;
		}

		public function get hammer():DataCommon.RewardItemCPP {
			return hammer$field;
		}

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.cash", "cash", (8 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var cash$field:DataCommon.RewardItemCPP;

		public function clearCash():void {
			cash$field = null;
		}

		public function get hasCash():Boolean {
			return cash$field != null;
		}

		public function set cash(value:DataCommon.RewardItemCPP):void {
			cash$field = value;
		}

		public function get cash():DataCommon.RewardItemCPP {
			return cash$field;
		}

		/**
		 *  @private
		 */
		public static const REFRESH:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.refresh", "refresh", (9 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var refresh$field:DataCommon.RewardItemCPP;

		public function clearRefresh():void {
			refresh$field = null;
		}

		public function get hasRefresh():Boolean {
			return refresh$field != null;
		}

		public function set refresh(value:DataCommon.RewardItemCPP):void {
			refresh$field = value;
		}

		public function get refresh():DataCommon.RewardItemCPP {
			return refresh$field;
		}

		/**
		 *  @private
		 */
		public static const AREFRESH:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.arefresh", "arefresh", (10 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var arefresh$field:DataCommon.RewardItemCPP;

		public function clearArefresh():void {
			arefresh$field = null;
		}

		public function get hasArefresh():Boolean {
			return arefresh$field != null;
		}

		public function set arefresh(value:DataCommon.RewardItemCPP):void {
			arefresh$field = value;
		}

		public function get arefresh():DataCommon.RewardItemCPP {
			return arefresh$field;
		}

		/**
		 *  @private
		 */
		public static const SACRIFICE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.sacrifice", "sacrifice", (11 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var sacrifice$field:DataCommon.RewardItemCPP;

		public function clearSacrifice():void {
			sacrifice$field = null;
		}

		public function get hasSacrifice():Boolean {
			return sacrifice$field != null;
		}

		public function set sacrifice(value:DataCommon.RewardItemCPP):void {
			sacrifice$field = value;
		}

		public function get sacrifice():DataCommon.RewardItemCPP {
			return sacrifice$field;
		}

		/**
		 *  @private
		 */
		public static const MARKET:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.market", "market", (12 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var market$field:DataCommon.RewardItemCPP;

		public function clearMarket():void {
			market$field = null;
		}

		public function get hasMarket():Boolean {
			return market$field != null;
		}

		public function set market(value:DataCommon.RewardItemCPP):void {
			market$field = value;
		}

		public function get market():DataCommon.RewardItemCPP {
			return market$field;
		}

		/**
		 *  @private
		 */
		public static const SHADOW:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("DataCommon.CommonBaseRewardCPP.shadow", "shadow", (13 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		private var shadow$field:DataCommon.RewardItemCPP;

		public function clearShadow():void {
			shadow$field = null;
		}

		public function get hasShadow():Boolean {
			return shadow$field != null;
		}

		public function set shadow(value:DataCommon.RewardItemCPP):void {
			shadow$field = value;
		}

		public function get shadow():DataCommon.RewardItemCPP {
			return shadow$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasFood) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, food$field);
			}
			if (hasIron) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, iron$field);
			}
			if (hasOrder) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, order$field);
			}
			if (hasExp) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, exp$field);
			}
			if (hasCoin) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, coin$field);
			}
			if (hasWood) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, wood$field);
			}
			if (hasHammer) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, hammer$field);
			}
			if (hasCash) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 8);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, cash$field);
			}
			if (hasRefresh) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 9);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, refresh$field);
			}
			if (hasArefresh) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 10);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, arefresh$field);
			}
			if (hasSacrifice) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 11);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, sacrifice$field);
			}
			if (hasMarket) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 12);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, market$field);
			}
			if (hasShadow) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 13);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, shadow$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var food$count:uint = 0;
			var iron$count:uint = 0;
			var order$count:uint = 0;
			var exp$count:uint = 0;
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var hammer$count:uint = 0;
			var cash$count:uint = 0;
			var refresh$count:uint = 0;
			var arefresh$count:uint = 0;
			var sacrifice$count:uint = 0;
			var market$count:uint = 0;
			var shadow$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.food cannot be set twice.');
					}
					++food$count;
					this.food = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.food);
					break;
				case 2:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.iron);
					break;
				case 3:
					if (order$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.order cannot be set twice.');
					}
					++order$count;
					this.order = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.order);
					break;
				case 4:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.exp);
					break;
				case 5:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.coin);
					break;
				case 6:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.wood);
					break;
				case 7:
					if (hammer$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.hammer cannot be set twice.');
					}
					++hammer$count;
					this.hammer = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.hammer);
					break;
				case 8:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.cash);
					break;
				case 9:
					if (refresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.refresh cannot be set twice.');
					}
					++refresh$count;
					this.refresh = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.refresh);
					break;
				case 10:
					if (arefresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.arefresh cannot be set twice.');
					}
					++arefresh$count;
					this.arefresh = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.arefresh);
					break;
				case 11:
					if (sacrifice$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.sacrifice cannot be set twice.');
					}
					++sacrifice$count;
					this.sacrifice = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.sacrifice);
					break;
				case 12:
					if (market$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.market cannot be set twice.');
					}
					++market$count;
					this.market = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.market);
					break;
				case 13:
					if (shadow$count != 0) {
						throw new flash.errors.IOError('Bad data format: CommonBaseRewardCPP.shadow cannot be set twice.');
					}
					++shadow$count;
					this.shadow = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.shadow);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
