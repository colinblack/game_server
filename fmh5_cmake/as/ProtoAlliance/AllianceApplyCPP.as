package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceApplyCPP
	{
		public static const PROTO:String = "ProtoAlliance.AllianceApplyCPP";
		public var package_root:*;
		public  var message:*;
		public var applyUid:int;
		public var name:Byte;
		public var reason:Byte;
		public var applyts:int;
		public function AllianceApplyCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			applyUid = undefined;
			name = undefined;
			reason = undefined;
			applyts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.applyUid = this.applyUid;
			if(this.name!= undefined)
			{
				serializeObj.name = this.name.getUint8Array(0, this.name.length);
				this.name.pos = 0;
			}
			this.reason.pos = 0;
			serializeObj.applyts = this.applyts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceApplyCPP
		{
			applyUid = undefined;
			name = undefined;
			reason = undefined;
			applyts = undefined;
			this.applyUid = msgObj.applyUid;
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = new Byte();
				this.name.writeArrayBuffer(msgObj.name);
				this.name.pos = 0;
			}
			this.reason = new Byte();
			this.reason.writeArrayBuffer(msgObj.reason);
			this.reason.pos = 0;
			this.applyts = msgObj.applyts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceApplyCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}