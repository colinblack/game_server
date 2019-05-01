package DataConfig {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class BaseRewardConfigCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.coin", "coin", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		private var coin$field:uint;

		private var hasField$0:uint = 0;

		public function clearCoin():void {
			hasField$0 &= 0xfffffffe;
			coin$field = new uint();
		}

		public function get hasCoin():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set coin(value:uint):void {
			hasField$0 |= 0x1;
			coin$field = value;
		}

		public function get coin():uint {
			return coin$field;
		}

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.wood", "wood", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		private var wood$field:uint;

		public function clearWood():void {
			hasField$0 &= 0xfffffffd;
			wood$field = new uint();
		}

		public function get hasWood():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set wood(value:uint):void {
			hasField$0 |= 0x2;
			wood$field = value;
		}

		public function get wood():uint {
			return wood$field;
		}

		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.food", "food", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		private var food$field:uint;

		public function clearFood():void {
			hasField$0 &= 0xfffffffb;
			food$field = new uint();
		}

		public function get hasFood():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set food(value:uint):void {
			hasField$0 |= 0x4;
			food$field = value;
		}

		public function get food():uint {
			return food$field;
		}

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.iron", "iron", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		private var iron$field:uint;

		public function clearIron():void {
			hasField$0 &= 0xfffffff7;
			iron$field = new uint();
		}

		public function get hasIron():Boolean {
			return (hasField$0 & 0x8) != 0;
		}

		public function set iron(value:uint):void {
			hasField$0 |= 0x8;
			iron$field = value;
		}

		public function get iron():uint {
			return iron$field;
		}

		/**
		 *  @private
		 */
		public static const HAMMER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.hammer", "hammer", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var hammer$field:uint;

		public function clearHammer():void {
			hasField$0 &= 0xffffffef;
			hammer$field = new uint();
		}

		public function get hasHammer():Boolean {
			return (hasField$0 & 0x10) != 0;
		}

		public function set hammer(value:uint):void {
			hasField$0 |= 0x10;
			hammer$field = value;
		}

		public function get hammer():uint {
			return hammer$field;
		}

		/**
		 *  @private
		 */
		public static const ORDER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.order", "order", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		private var order$field:uint;

		public function clearOrder():void {
			hasField$0 &= 0xffffffdf;
			order$field = new uint();
		}

		public function get hasOrder():Boolean {
			return (hasField$0 & 0x20) != 0;
		}

		public function set order(value:uint):void {
			hasField$0 |= 0x20;
			order$field = value;
		}

		public function get order():uint {
			return order$field;
		}

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.exp", "exp", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		private var exp$field:uint;

		public function clearExp():void {
			hasField$0 &= 0xffffffbf;
			exp$field = new uint();
		}

		public function get hasExp():Boolean {
			return (hasField$0 & 0x40) != 0;
		}

		public function set exp(value:uint):void {
			hasField$0 |= 0x40;
			exp$field = value;
		}

		public function get exp():uint {
			return exp$field;
		}

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.cash", "cash", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		private var cash$field:uint;

		public function clearCash():void {
			hasField$0 &= 0xffffff7f;
			cash$field = new uint();
		}

		public function get hasCash():Boolean {
			return (hasField$0 & 0x80) != 0;
		}

		public function set cash(value:uint):void {
			hasField$0 |= 0x80;
			cash$field = value;
		}

		public function get cash():uint {
			return cash$field;
		}

		/**
		 *  @private
		 */
		public static const REFRESH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.refresh", "refresh", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		private var refresh$field:uint;

		public function clearRefresh():void {
			hasField$0 &= 0xfffffeff;
			refresh$field = new uint();
		}

		public function get hasRefresh():Boolean {
			return (hasField$0 & 0x100) != 0;
		}

		public function set refresh(value:uint):void {
			hasField$0 |= 0x100;
			refresh$field = value;
		}

		public function get refresh():uint {
			return refresh$field;
		}

		/**
		 *  @private
		 */
		public static const AREFRESH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.arefresh", "arefresh", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		private var arefresh$field:uint;

		public function clearArefresh():void {
			hasField$0 &= 0xfffffdff;
			arefresh$field = new uint();
		}

		public function get hasArefresh():Boolean {
			return (hasField$0 & 0x200) != 0;
		}

		public function set arefresh(value:uint):void {
			hasField$0 |= 0x200;
			arefresh$field = value;
		}

		public function get arefresh():uint {
			return arefresh$field;
		}

		/**
		 *  @private
		 */
		public static const SACRIFICE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.sacrifice", "sacrifice", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		private var sacrifice$field:uint;

		public function clearSacrifice():void {
			hasField$0 &= 0xfffffbff;
			sacrifice$field = new uint();
		}

		public function get hasSacrifice():Boolean {
			return (hasField$0 & 0x400) != 0;
		}

		public function set sacrifice(value:uint):void {
			hasField$0 |= 0x400;
			sacrifice$field = value;
		}

		public function get sacrifice():uint {
			return sacrifice$field;
		}

		/**
		 *  @private
		 */
		public static const MARKET:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.market", "market", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		private var market$field:uint;

		public function clearMarket():void {
			hasField$0 &= 0xfffff7ff;
			market$field = new uint();
		}

		public function get hasMarket():Boolean {
			return (hasField$0 & 0x800) != 0;
		}

		public function set market(value:uint):void {
			hasField$0 |= 0x800;
			market$field = value;
		}

		public function get market():uint {
			return market$field;
		}

		/**
		 *  @private
		 */
		public static const SHADOW:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataConfig.BaseRewardConfigCPP.shadow", "shadow", (13 << 3) | com.netease.protobuf.WireType.VARINT);

		private var shadow$field:uint;

		public function clearShadow():void {
			hasField$0 &= 0xffffefff;
			shadow$field = new uint();
		}

		public function get hasShadow():Boolean {
			return (hasField$0 & 0x1000) != 0;
		}

		public function set shadow(value:uint):void {
			hasField$0 |= 0x1000;
			shadow$field = value;
		}

		public function get shadow():uint {
			return shadow$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasCoin) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, coin$field);
			}
			if (hasWood) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, wood$field);
			}
			if (hasFood) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, food$field);
			}
			if (hasIron) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, iron$field);
			}
			if (hasHammer) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, hammer$field);
			}
			if (hasOrder) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, order$field);
			}
			if (hasExp) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, exp$field);
			}
			if (hasCash) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, cash$field);
			}
			if (hasRefresh) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, refresh$field);
			}
			if (hasArefresh) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, arefresh$field);
			}
			if (hasSacrifice) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, sacrifice$field);
			}
			if (hasMarket) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, market$field);
			}
			if (hasShadow) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 13);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, shadow$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var food$count:uint = 0;
			var iron$count:uint = 0;
			var hammer$count:uint = 0;
			var order$count:uint = 0;
			var exp$count:uint = 0;
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
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.food cannot be set twice.');
					}
					++food$count;
					this.food = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (hammer$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.hammer cannot be set twice.');
					}
					++hammer$count;
					this.hammer = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (order$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.order cannot be set twice.');
					}
					++order$count;
					this.order = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (refresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.refresh cannot be set twice.');
					}
					++refresh$count;
					this.refresh = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (arefresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.arefresh cannot be set twice.');
					}
					++arefresh$count;
					this.arefresh = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (sacrifice$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.sacrifice cannot be set twice.');
					}
					++sacrifice$count;
					this.sacrifice = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 12:
					if (market$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.market cannot be set twice.');
					}
					++market$count;
					this.market = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 13:
					if (shadow$count != 0) {
						throw new flash.errors.IOError('Bad data format: BaseRewardConfigCPP.shadow cannot be set twice.');
					}
					++shadow$count;
					this.shadow = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
