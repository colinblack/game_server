package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceMemberCPP
	{
		public static const PROTO:String = "ProtoAlliance.AllianceMemberCPP";
		public var package_root:*;
		public  var message:*;
		public var memberUid:int;
		public var name:Byte;
		public var position:int;
		public var authority:int;
		public var helptimes:int;
		public var onlineTs:int;
		public var helpTs:int;
		public var level:int;
		public var fig:Byte;
		public var joinTs:int;
		public function AllianceMemberCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			memberUid = undefined;
			name = undefined;
			position = undefined;
			authority = undefined;
			helptimes = undefined;
			onlineTs = undefined;
			helpTs = undefined;
			level = undefined;
			fig = undefined;
			joinTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.memberUid = this.memberUid;
			if(this.name!= undefined)
			{
				serializeObj.name = this.name.getUint8Array(0, this.name.length);
				this.name.pos = 0;
			}
			serializeObj.position = this.position;
			serializeObj.authority = this.authority;
			serializeObj.helptimes = this.helptimes;
			serializeObj.onlineTs = this.onlineTs;
			if(this.helpTs!= undefined)
			{
				serializeObj.helpTs = this.helpTs;
			}
			serializeObj.level = this.level;
			if(this.fig!= undefined)
			{
				serializeObj.fig = this.fig.getUint8Array(0, this.fig.length);
				this.fig.pos = 0;
			}
			if(this.joinTs!= undefined)
			{
				serializeObj.joinTs = this.joinTs;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceMemberCPP
		{
			memberUid = undefined;
			name = undefined;
			position = undefined;
			authority = undefined;
			helptimes = undefined;
			onlineTs = undefined;
			helpTs = undefined;
			level = undefined;
			fig = undefined;
			joinTs = undefined;
			this.memberUid = msgObj.memberUid;
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = new Byte();
				this.name.writeArrayBuffer(msgObj.name);
				this.name.pos = 0;
			}
			this.position = msgObj.position;
			this.authority = msgObj.authority;
			this.helptimes = msgObj.helptimes;
			this.onlineTs = msgObj.onlineTs;
			if(msgObj.hasOwnProperty("helpTs"))
			{
				this.helpTs = msgObj.helpTs;
			}
			this.level = msgObj.level;
			if(msgObj.hasOwnProperty("fig"))
			{
				this.fig = new Byte();
				this.fig.writeArrayBuffer(msgObj.fig);
				this.fig.pos = 0;
			}
			if(msgObj.hasOwnProperty("joinTs"))
			{
				this.joinTs = msgObj.joinTs;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceMemberCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}