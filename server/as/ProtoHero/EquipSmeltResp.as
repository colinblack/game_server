package ProtoHero {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoHero.HeroBaseInfoCPP;
	import DataCommon.EquipmentCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class EquipSmeltResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUIP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoHero.EquipSmeltResp.equip", "equip", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentCPP; });

		public var equip:DataCommon.EquipmentCPP;

		/**
		 *  @private
		 */
		public static const HERO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoHero.EquipSmeltResp.hero", "hero", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoHero.HeroBaseInfoCPP; });

		public var hero:ProtoHero.HeroBaseInfoCPP;

		/**
		 *  @private
		 */
		public static const REFRESH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.EquipSmeltResp.refresh", "refresh", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var refresh:uint;

		/**
		 *  @private
		 */
		public static const AREFRESH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.EquipSmeltResp.arefresh", "arefresh", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var arefresh:uint;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoHero.EquipSmeltResp.cash", "cash", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equip);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.hero);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.refresh);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.arefresh);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var equip$count:uint = 0;
			var hero$count:uint = 0;
			var refresh$count:uint = 0;
			var arefresh$count:uint = 0;
			var cash$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equip$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipSmeltResp.equip cannot be set twice.');
					}
					++equip$count;
					this.equip = new DataCommon.EquipmentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equip);
					break;
				case 2:
					if (hero$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipSmeltResp.hero cannot be set twice.');
					}
					++hero$count;
					this.hero = new ProtoHero.HeroBaseInfoCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.hero);
					break;
				case 3:
					if (refresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipSmeltResp.refresh cannot be set twice.');
					}
					++refresh$count;
					this.refresh = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (arefresh$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipSmeltResp.arefresh cannot be set twice.');
					}
					++arefresh$count;
					this.arefresh = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipSmeltResp.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
