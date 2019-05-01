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
	import ProtoOfficial.DepartmentMember;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ApplyExitResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const DEPARTMENT:FieldDescriptor_TYPE_ENUM = new FieldDescriptor_TYPE_ENUM("ProtoOfficial.ApplyExitResp.department", "department", (1 << 3) | com.netease.protobuf.WireType.VARINT, ProtoOfficial.eDepartment);

		public var department:int;

		/**
		 *  @private
		 */
		public static const OFFICIAL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.ApplyExitResp.official", "official", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var official:uint;

		/**
		 *  @private
		 */
		public static const PRESTIGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.ApplyExitResp.prestige", "prestige", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var prestige:uint;

		/**
		 *  @private
		 */
		public static const MEMBERS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoOfficial.ApplyExitResp.members", "members", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOfficial.DepartmentMember; });

		[ArrayElementType("ProtoOfficial.DepartmentMember")]
		public var members:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_ENUM(output, this.department);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.official);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.prestige);
			for (var members$index:uint = 0; members$index < this.members.length; ++members$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.members[members$index]);
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
			var official$count:uint = 0;
			var prestige$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (department$count != 0) {
						throw new flash.errors.IOError('Bad data format: ApplyExitResp.department cannot be set twice.');
					}
					++department$count;
					this.department = com.netease.protobuf.ReadUtils.read_TYPE_ENUM(input);
					break;
				case 2:
					if (official$count != 0) {
						throw new flash.errors.IOError('Bad data format: ApplyExitResp.official cannot be set twice.');
					}
					++official$count;
					this.official = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (prestige$count != 0) {
						throw new flash.errors.IOError('Bad data format: ApplyExitResp.prestige cannot be set twice.');
					}
					++prestige$count;
					this.prestige = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					this.members.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoOfficial.DepartmentMember()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
