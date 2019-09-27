package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class FolkCPP
	{
		public static const PROTO:String = "ProtoFriend.FolkCPP";
		public var package_root:*;
		public  var message:*;
		public var folkUid:int;
		public var level:int;
		public var fig:Byte;
		public var name:Byte;
		public var needhelp:Boolean;
		public var blueInfo:int;
		public function FolkCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			folkUid = undefined;
			level = undefined;
			fig = undefined;
			name = undefined;
			needhelp = undefined;
			blueInfo = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.folkUid = this.folkUid;
			if(this.level!= undefined)
			{
				serializeObj.level = this.level;
			}
			if(this.fig!= undefined)
			{
				serializeObj.fig = this.fig.getUint8Array(0, this.fig.length);
				this.fig.pos = 0;
			}
			if(this.name!= undefined)
			{
				serializeObj.name = this.name.getUint8Array(0, this.name.length);
				this.name.pos = 0;
			}
			if(this.needhelp!= undefined)
			{
				serializeObj.needhelp = this.needhelp;
			}
			if(this.blueInfo!= undefined)
			{
				serializeObj.blueInfo = this.blueInfo;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):FolkCPP
		{
			folkUid = undefined;
			level = undefined;
			fig = undefined;
			name = undefined;
			needhelp = undefined;
			blueInfo = undefined;
			this.folkUid = msgObj.folkUid;
			if(msgObj.hasOwnProperty("level"))
			{
				this.level = msgObj.level;
			}
			if(msgObj.hasOwnProperty("fig"))
			{
				this.fig = new Byte();
				this.fig.writeArrayBuffer(msgObj.fig);
				this.fig.pos = 0;
			}
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = new Byte();
				this.name.writeArrayBuffer(msgObj.name);
				this.name.pos = 0;
			}
			if(msgObj.hasOwnProperty("needhelp"))
			{
				this.needhelp = msgObj.needhelp;
			}
			if(msgObj.hasOwnProperty("blueInfo"))
			{
				this.blueInfo = msgObj.blueInfo;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FolkCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}