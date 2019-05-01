package ProtoMarket {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoMarket.MarketCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PurchaseMarketResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.PurchaseMarketResp.coin", "coin", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const MARKETTIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.PurchaseMarketResp.markettime", "markettime", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var markettime:uint;

		/**
		 *  @private
		 */
		public static const MARKET:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoMarket.PurchaseMarketResp.market", "market", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoMarket.MarketCPP; });

		public var market:ProtoMarket.MarketCPP;

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.PurchaseMarketResp.wood", "wood", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		private var wood$field:uint;

		private var hasField$0:uint = 0;

		public function clearWood():void {
			hasField$0 &= 0xfffffffe;
			wood$field = new uint();
		}

		public function get hasWood():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set wood(value:uint):void {
			hasField$0 |= 0x1;
			wood$field = value;
		}

		public function get wood():uint {
			return wood$field;
		}

		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.PurchaseMarketResp.food", "food", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var food$field:uint;

		public function clearFood():void {
			hasField$0 &= 0xfffffffd;
			food$field = new uint();
		}

		public function get hasFood():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set food(value:uint):void {
			hasField$0 |= 0x2;
			food$field = value;
		}

		public function get food():uint {
			return food$field;
		}

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.PurchaseMarketResp.iron", "iron", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		private var iron$field:uint;

		public function clearIron():void {
			hasField$0 &= 0xfffffffb;
			iron$field = new uint();
		}

		public function get hasIron():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set iron(value:uint):void {
			hasField$0 |= 0x4;
			iron$field = value;
		}

		public function get iron():uint {
			return iron$field;
		}

		/**
		 *  @private
		 */
		public static const ORDER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.PurchaseMarketResp.order", "order", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		private var order$field:uint;

		public function clearOrder():void {
			hasField$0 &= 0xfffffff7;
			order$field = new uint();
		}

		public function get hasOrder():Boolean {
			return (hasField$0 & 0x8) != 0;
		}

		public function set order(value:uint):void {
			hasField$0 |= 0x8;
			order$field = value;
		}

		public function get order():uint {
			return order$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.markettime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.market);
			if (hasWood) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, wood$field);
			}
			if (hasFood) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, food$field);
			}
			if (hasIron) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, iron$field);
			}
			if (hasOrder) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, order$field);
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
			var markettime$count:uint = 0;
			var market$count:uint = 0;
			var wood$count:uint = 0;
			var food$count:uint = 0;
			var iron$count:uint = 0;
			var order$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseMarketResp.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (markettime$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseMarketResp.markettime cannot be set twice.');
					}
					++markettime$count;
					this.markettime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (market$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseMarketResp.market cannot be set twice.');
					}
					++market$count;
					this.market = new ProtoMarket.MarketCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.market);
					break;
				case 4:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseMarketResp.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseMarketResp.food cannot be set twice.');
					}
					++food$count;
					this.food = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseMarketResp.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (order$count != 0) {
						throw new flash.errors.IOError('Bad data format: PurchaseMarketResp.order cannot be set twice.');
					}
					++order$count;
					this.order = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
