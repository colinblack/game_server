package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class CheckNameAvailableResp
	{
		public static const PROTO:String = "ProtoAlliance.CheckNameAvailableResp";
		public var package_root:*;
		public  var message:*;
		public var name:Byte;
		public var isAvailable:Boolean;
		public var reason:Byte;
		public function CheckNameAvailableResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			name = undefined;
			isAvailable = undefined;
			reason = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			this.name.pos = 0;
			serializeObj.isAvailable = this.isAvailable;
			if(this.reason!= undefined)
			{
				serializeObj.reason = this.reason.getUint8Array(0, this.reason.length);
				this.reason.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CheckNameAvailableResp
		{
			name = undefined;
			isAvailable = undefined;
			reason = undefined;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.isAvailable = msgObj.isAvailable;
			if(msgObj.hasOwnProperty("reason"))
			{
				this.reason = new Byte();
				this.reason.writeArrayBuffer(msgObj.reason);
				this.reason.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CheckNameAvailableResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}