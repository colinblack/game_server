package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestUpdateMemberBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestUpdateMemberBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var onlineTs:int;
		public var helpTs:int;
		public var level:int;
		public var name:Byte;
		public var vipLevel:int;
		public function RequestUpdateMemberBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			onlineTs = undefined;
			helpTs = undefined;
			level = undefined;
			name = undefined;
			vipLevel = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			if(this.onlineTs!= undefined)
			{
				serializeObj.onlineTs = this.onlineTs;
			}
			if(this.helpTs!= undefined)
			{
				serializeObj.helpTs = this.helpTs;
			}
			if(this.level!= undefined)
			{
				serializeObj.level = this.level;
			}
			if(this.name!= undefined)
			{
				serializeObj.name = this.name.getUint8Array(0, this.name.length);
				this.name.pos = 0;
			}
			if(this.vipLevel!= undefined)
			{
				serializeObj.vipLevel = this.vipLevel;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestUpdateMemberBC
		{
			aid = undefined;
			uid = undefined;
			onlineTs = undefined;
			helpTs = undefined;
			level = undefined;
			name = undefined;
			vipLevel = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			if(msgObj.hasOwnProperty("onlineTs"))
			{
				this.onlineTs = msgObj.onlineTs;
			}
			if(msgObj.hasOwnProperty("helpTs"))
			{
				this.helpTs = msgObj.helpTs;
			}
			if(msgObj.hasOwnProperty("level"))
			{
				this.level = msgObj.level;
			}
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = new Byte();
				this.name.writeArrayBuffer(msgObj.name);
				this.name.pos = 0;
			}
			if(msgObj.hasOwnProperty("vipLevel"))
			{
				this.vipLevel = msgObj.vipLevel;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestUpdateMemberBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}