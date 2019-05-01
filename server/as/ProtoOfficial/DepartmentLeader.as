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
	public dynamic final class DepartmentLeader extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const TYPE:FieldDescriptor_TYPE_ENUM = new FieldDescriptor_TYPE_ENUM("ProtoOfficial.DepartmentLeader.type", "type", (1 << 3) | com.netease.protobuf.WireType.VARINT, ProtoOfficial.eDepartment);

		public var type:int;

		/**
		 *  @private
		 */
		public static const LEADER:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoOfficial.DepartmentLeader.leader", "leader", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOfficial.DepartmentMember; });

		public var leader:ProtoOfficial.DepartmentMember;

		/**
		 *  @private
		 */
		public static const PRESTIGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOfficial.DepartmentLeader.prestige", "prestige", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var prestige:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_ENUM(output, this.type);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.leader);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.prestige);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var type$count:uint = 0;
			var leader$count:uint = 0;
			var prestige$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (type$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentLeader.type cannot be set twice.');
					}
					++type$count;
					this.type = com.netease.protobuf.ReadUtils.read_TYPE_ENUM(input);
					break;
				case 2:
					if (leader$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentLeader.leader cannot be set twice.');
					}
					++leader$count;
					this.leader = new ProtoOfficial.DepartmentMember();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.leader);
					break;
				case 3:
					if (prestige$count != 0) {
						throw new flash.errors.IOError('Bad data format: DepartmentLeader.prestige cannot be set twice.');
					}
					++prestige$count;
					this.prestige = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
