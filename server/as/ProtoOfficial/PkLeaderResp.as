package ProtoOfficial {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoOfficial.eDepartment;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class PkLeaderResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const DEPARTMENT:FieldDescriptor_TYPE_ENUM = new FieldDescriptor_TYPE_ENUM("ProtoOfficial.PkLeaderResp.department", "department", (1 << 3) | com.netease.protobuf.WireType.VARINT, ProtoOfficial.eDepartment);

		public var department:int;

		/**
		 *  @private
		 */
		public static const HERO_IDS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoOfficial.PkLeaderResp.hero_ids", "heroIds", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var heroIds:Array = [];

		/**
		 *  @private
		 */
		public static const HERO_LVL:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoOfficial.PkLeaderResp.hero_lvl", "heroLvl", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var heroLvl:Array = [];

		/**
		 *  @private
		 */
		public static const HERO_TROOPS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoOfficial.PkLeaderResp.hero_troops", "heroTroops", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var heroTroops:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_ENUM(output, this.department);
			for (var heroIds$index:uint = 0; heroIds$index < this.heroIds.length; ++heroIds$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroIds[heroIds$index]);
			}
			for (var heroLvl$index:uint = 0; heroLvl$index < this.heroLvl.length; ++heroLvl$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroLvl[heroLvl$index]);
			}
			for (var heroTroops$index:uint = 0; heroTroops$index < this.heroTroops.length; ++heroTroops$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroTroops[heroTroops$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var department$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (department$count != 0) {
						throw new flash.errors.IOError('Bad data format: PkLeaderResp.department cannot be set twice.');
					}
					++department$count;
					this.department = com.netease.protobuf.ReadUtils.read_TYPE_ENUM(input);
					break;
				case 2:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.heroIds);
						break;
					}
					this.heroIds.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 3:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.heroLvl);
						break;
					}
					this.heroLvl.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 4:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.heroTroops);
						break;
					}
					this.heroTroops.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
