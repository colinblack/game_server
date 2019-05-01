package ProtoBattleField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import flash.utils.ByteArray;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ReplyCityMaster extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.uid", "uid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const NAME:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoBattleField.ReplyCityMaster.name", "name", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var name$field:flash.utils.ByteArray;

		public function clearName():void {
			name$field = null;
		}

		public function get hasName():Boolean {
			return name$field != null;
		}

		public function set name(value:flash.utils.ByteArray):void {
			name$field = value;
		}

		public function get name():flash.utils.ByteArray {
			return name$field;
		}

		/**
		 *  @private
		 */
		public static const AID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.aid", "aid", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		private var aid$field:uint;

		private var hasField$0:uint = 0;

		public function clearAid():void {
			hasField$0 &= 0xfffffffe;
			aid$field = new uint();
		}

		public function get hasAid():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set aid(value:uint):void {
			hasField$0 |= 0x1;
			aid$field = value;
		}

		public function get aid():uint {
			return aid$field;
		}

		/**
		 *  @private
		 */
		public static const JOB:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.job", "job", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		private var job$field:uint;

		public function clearJob():void {
			hasField$0 &= 0xfffffffd;
			job$field = new uint();
		}

		public function get hasJob():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set job(value:uint):void {
			hasField$0 |= 0x2;
			job$field = value;
		}

		public function get job():uint {
			return job$field;
		}

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.level", "level", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var level$field:uint;

		public function clearLevel():void {
			hasField$0 &= 0xfffffffb;
			level$field = new uint();
		}

		public function get hasLevel():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set level(value:uint):void {
			hasField$0 |= 0x4;
			level$field = value;
		}

		public function get level():uint {
			return level$field;
		}

		/**
		 *  @private
		 */
		public static const HERO_IDS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.hero_ids", "heroIds", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var heroIds:Array = [];

		/**
		 *  @private
		 */
		public static const HERO_LVL:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.hero_lvl", "heroLvl", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var heroLvl:Array = [];

		/**
		 *  @private
		 */
		public static const HERO_TROOPS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.hero_troops", "heroTroops", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var heroTroops:Array = [];

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.reward", "reward", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var reward:uint;

		/**
		 *  @private
		 */
		public static const NEXT_REWARD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.next_reward", "nextReward", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		public var nextReward:uint;

		/**
		 *  @private
		 */
		public static const CCD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.ccd", "ccd", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ccd:uint;

		/**
		 *  @private
		 */
		public static const CTIMES:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCityMaster.ctimes", "ctimes", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ctimes:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			if (hasName) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, name$field);
			}
			if (hasAid) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, aid$field);
			}
			if (hasJob) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, job$field);
			}
			if (hasLevel) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, level$field);
			}
			for (var heroIds$index:uint = 0; heroIds$index < this.heroIds.length; ++heroIds$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroIds[heroIds$index]);
			}
			for (var heroLvl$index:uint = 0; heroLvl$index < this.heroLvl.length; ++heroLvl$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroLvl[heroLvl$index]);
			}
			for (var heroTroops$index:uint = 0; heroTroops$index < this.heroTroops.length; ++heroTroops$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroTroops[heroTroops$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.reward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.nextReward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ccd);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ctimes);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var uid$count:uint = 0;
			var name$count:uint = 0;
			var aid$count:uint = 0;
			var job$count:uint = 0;
			var level$count:uint = 0;
			var reward$count:uint = 0;
			var next_reward$count:uint = 0;
			var ccd$count:uint = 0;
			var ctimes$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (name$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.name cannot be set twice.');
					}
					++name$count;
					this.name = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 3:
					if (aid$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.aid cannot be set twice.');
					}
					++aid$count;
					this.aid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (job$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.job cannot be set twice.');
					}
					++job$count;
					this.job = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.heroIds);
						break;
					}
					this.heroIds.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 7:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.heroLvl);
						break;
					}
					this.heroLvl.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 8:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.heroTroops);
						break;
					}
					this.heroTroops.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 9:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (next_reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.nextReward cannot be set twice.');
					}
					++next_reward$count;
					this.nextReward = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (ccd$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.ccd cannot be set twice.');
					}
					++ccd$count;
					this.ccd = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 12:
					if (ctimes$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCityMaster.ctimes cannot be set twice.');
					}
					++ctimes$count;
					this.ctimes = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
