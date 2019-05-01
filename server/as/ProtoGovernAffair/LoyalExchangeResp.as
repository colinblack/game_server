package ProtoGovernAffair {
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
	public dynamic final class LoyalExchangeResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoGovernAffair.LoyalExchangeResp.coin", "coin", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		public var coin:DataCommon.RewardItemCPP;

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoGovernAffair.LoyalExchangeResp.wood", "wood", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		public var wood:DataCommon.RewardItemCPP;

		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoGovernAffair.LoyalExchangeResp.food", "food", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		public var food:DataCommon.RewardItemCPP;

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoGovernAffair.LoyalExchangeResp.iron", "iron", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		public var iron:DataCommon.RewardItemCPP;

		/**
		 *  @private
		 */
		public static const LOYAL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoGovernAffair.LoyalExchangeResp.loyal", "loyal", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var loyal:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.wood);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.food);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.iron);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.loyal);
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
			var loyal$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoyalExchangeResp.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.coin);
					break;
				case 2:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoyalExchangeResp.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.wood);
					break;
				case 3:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoyalExchangeResp.food cannot be set twice.');
					}
					++food$count;
					this.food = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.food);
					break;
				case 4:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoyalExchangeResp.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.iron);
					break;
				case 5:
					if (loyal$count != 0) {
						throw new flash.errors.IOError('Bad data format: LoyalExchangeResp.loyal cannot be set twice.');
					}
					++loyal$count;
					this.loyal = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
