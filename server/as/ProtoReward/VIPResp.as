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
	public dynamic final class VIPResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUIPS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoReward.VIPResp.equips", "equips", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentAllCPP; });

		public var equips:DataCommon.EquipmentAllCPP;

		/**
		 *  @private
		 */
		public static const EQUIPS_ID:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoReward.VIPResp.equips_id", "equipsId", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var equipsId:Array = [];

		/**
		 *  @private
		 */
		public static const EQUIPS_CNT:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoReward.VIPResp.equips_cnt", "equipsCnt", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var equipsCnt:Array = [];

		/**
		 *  @private
		 */
		public static const BASE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoReward.VIPResp.base", "base", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.CommonBaseRewardCPP; });

		public var base:DataCommon.CommonBaseRewardCPP;

		/**
		 *  @private
		 */
		public static const HEROS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoReward.VIPResp.heros", "heros", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoHero.HeroBaseInfoCPP; });

		[ArrayElementType("ProtoHero.HeroBaseInfoCPP")]
		public var heros:Array = [];

		/**
		 *  @private
		 */
		public static const VIP_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoReward.VIPResp.vip_level", "vipLevel", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var vipLevel:uint;

		/**
		 *  @private
		 */
		public static const VIP_REWARD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoReward.VIPResp.vip_reward", "vipReward", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var vipReward:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equips);
			for (var equipsId$index:uint = 0; equipsId$index < this.equipsId.length; ++equipsId$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.equipsId[equipsId$index]);
			}
			for (var equipsCnt$index:uint = 0; equipsCnt$index < this.equipsCnt.length; ++equipsCnt$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.equipsCnt[equipsCnt$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.base);
			for (var heros$index:uint = 0; heros$index < this.heros.length; ++heros$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.heros[heros$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.vipLevel);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.vipReward);
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
			var vip_level$count:uint = 0;
			var vip_reward$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equips$count != 0) {
						throw new flash.errors.IOError('Bad data format: VIPResp.equips cannot be set twice.');
					}
					++equips$count;
					this.equips = new DataCommon.EquipmentAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equips);
					break;
				case 2:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.equipsId);
						break;
					}
					this.equipsId.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 3:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.equipsCnt);
						break;
					}
					this.equipsCnt.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 4:
					if (base$count != 0) {
						throw new flash.errors.IOError('Bad data format: VIPResp.base cannot be set twice.');
					}
					++base$count;
					this.base = new DataCommon.CommonBaseRewardCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.base);
					break;
				case 5:
					this.heros.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoHero.HeroBaseInfoCPP()));
					break;
				case 6:
					if (vip_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: VIPResp.vipLevel cannot be set twice.');
					}
					++vip_level$count;
					this.vipLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (vip_reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: VIPResp.vipReward cannot be set twice.');
					}
					++vip_reward$count;
					this.vipReward = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
