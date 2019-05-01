package ProtoReward {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.EquipmentAllCPP;
	import DataCommon.CommonBaseRewardCPP;
	import ProtoHero.HeroBaseInfoCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class FirstRechargeResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUIPS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoReward.FirstRechargeResp.equips", "equips", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentAllCPP; });

		public var equips:DataCommon.EquipmentAllCPP;

		/**
		 *  @private
		 */
		public static const EQUIPS_CNT:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoReward.FirstRechargeResp.equips_cnt", "equipsCnt", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var equipsCnt:Array = [];

		/**
		 *  @private
		 */
		public static const BASE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoReward.FirstRechargeResp.base", "base", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.CommonBaseRewardCPP; });

		public var base:DataCommon.CommonBaseRewardCPP;

		/**
		 *  @private
		 */
		public static const HEROS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoReward.FirstRechargeResp.heros", "heros", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoHero.HeroBaseInfoCPP; });

		[ArrayElementType("ProtoHero.HeroBaseInfoCPP")]
		public var heros:Array = [];

		/**
		 *  @private
		 */
		public static const FIRST_RECHARGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoReward.FirstRechargeResp.first_recharge", "firstRecharge", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var firstRecharge:uint;

		/**
		 *  @private
		 */
		public static const AUTO_BUILD_FLAG:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoReward.FirstRechargeResp.auto_build_flag", "autoBuildFlag", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var autoBuildFlag:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equips);
			for (var equipsCnt$index:uint = 0; equipsCnt$index < this.equipsCnt.length; ++equipsCnt$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.equipsCnt[equipsCnt$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.base);
			for (var heros$index:uint = 0; heros$index < this.heros.length; ++heros$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.heros[heros$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.firstRecharge);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.autoBuildFlag);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var equips$count:uint = 0;
			var base$count:uint = 0;
			var first_recharge$count:uint = 0;
			var auto_build_flag$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equips$count != 0) {
						throw new flash.errors.IOError('Bad data format: FirstRechargeResp.equips cannot be set twice.');
					}
					++equips$count;
					this.equips = new DataCommon.EquipmentAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equips);
					break;
				case 2:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.equipsCnt);
						break;
					}
					this.equipsCnt.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 3:
					if (base$count != 0) {
						throw new flash.errors.IOError('Bad data format: FirstRechargeResp.base cannot be set twice.');
					}
					++base$count;
					this.base = new DataCommon.CommonBaseRewardCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.base);
					break;
				case 4:
					this.heros.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoHero.HeroBaseInfoCPP()));
					break;
				case 5:
					if (first_recharge$count != 0) {
						throw new flash.errors.IOError('Bad data format: FirstRechargeResp.firstRecharge cannot be set twice.');
					}
					++first_recharge$count;
					this.firstRecharge = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (auto_build_flag$count != 0) {
						throw new flash.errors.IOError('Bad data format: FirstRechargeResp.autoBuildFlag cannot be set twice.');
					}
					++auto_build_flag$count;
					this.autoBuildFlag = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
