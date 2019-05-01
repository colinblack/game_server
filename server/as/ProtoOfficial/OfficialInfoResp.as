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
	import ProtoOfficial.DepartmentLeader;
	import flash.utils.ByteArray;
	import ProtoOfficial.DepartmentMember;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OfficialInfoResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const LEADERS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoOfficial.OfficialInfoResp.leaders", "leaders", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOfficial.DepartmentLeader; });

		[ArrayElementType("ProtoOfficial.DepartmentLeader")]
		public var leaders:Array = [];

		/**
		 *  @private
		 */
		public static const DEPARTMENT:FieldDescriptor_TYPE_ENUM = new FieldDescriptor_TYPE_ENUM("ProtoOfficial.OfficialInfoResp.department", "department", (2 << 3) | com.netease.protobuf.WireType.VARINT, ProtoOfficial.eDepartment);

		public var department:int;

		/**
		 *  @private
		 */
		public static const MEMBERS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoOfficial.OfficialInfoResp.members", "members", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOfficial.DepartmentMember; });

		[ArrayElementType("ProtoOfficial.DepartmentMember")]
		public var members:Array = [];

		/**
		 *  @private
		 */
		public static const COUNTRY_NOTICE:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoOfficial.OfficialInfoResp.country_notice", "countryNotice", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var countryNotice:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const DEPART_NOTICE:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoOfficial.OfficialInfoResp.depart_notice", "departNotice", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var departNotice:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var leaders$index:uint = 0; leaders$index < this.leaders.length; ++leaders$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.leaders[leaders$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_ENUM(output, this.department);
			for (var members$index:uint = 0; members$index < this.members.length; ++members$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.members[members$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.countryNotice);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.departNotice);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var department$count:uint = 0;
			var country_notice$count:uint = 0;
			var depart_notice$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.leaders.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoOfficial.DepartmentLeader()));
					break;
				case 2:
					if (department$count != 0) {
						throw new flash.errors.IOError('Bad data format: OfficialInfoResp.department cannot be set twice.');
					}
					++department$count;
					this.department = com.netease.protobuf.ReadUtils.read_TYPE_ENUM(input);
					break;
				case 3:
					this.members.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoOfficial.DepartmentMember()));
					break;
				case 4:
					if (country_notice$count != 0) {
						throw new flash.errors.IOError('Bad data format: OfficialInfoResp.countryNotice cannot be set twice.');
					}
					++country_notice$count;
					this.countryNotice = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 5:
					if (depart_notice$count != 0) {
						throw new flash.errors.IOError('Bad data format: OfficialInfoResp.departNotice cannot be set twice.');
					}
					++depart_notice$count;
					this.departNotice = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
