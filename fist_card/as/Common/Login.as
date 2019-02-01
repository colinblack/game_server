package com.sanguo.game.server.connectlogic.common.message.Common
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class Login
	{
		public static const PROTO:String = "Common.Login";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var openid:String;
		public var openkey:String;
		public var ts:int;
		public var sig:String;
		public var isnew:Boolean;
		public var platform:int;
		public var fig:Byte;
		public var name:Byte;
		public var uuid:int;
		public var uact:int;
		public var uts:int;
		public var uinfo:int;
		public function Login(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
			openid = undefined;
			openkey = undefined;
			ts = undefined;
			sig = undefined;
			isnew = undefined;
			platform = undefined;
			fig = undefined;
			name = undefined;
			uuid = undefined;
			uact = undefined;
			uts = undefined;
			uinfo = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.openid = this.openid;
			serializeObj.openkey = this.openkey;
			serializeObj.ts = this.ts;
			serializeObj.sig = this.sig;
			serializeObj.isnew = this.isnew;
			serializeObj.platform = this.platform;
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
			if(this.uuid!= undefined)
			{
				serializeObj.uuid = this.uuid;
			}
			if(this.uact!= undefined)
			{
				serializeObj.uact = this.uact;
			}
			if(this.uts!= undefined)
			{
				serializeObj.uts = this.uts;
			}
			if(this.uinfo!= undefined)
			{
				serializeObj.uinfo = this.uinfo;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):Login
		{
			uid = undefined;
			openid = undefined;
			openkey = undefined;
			ts = undefined;
			sig = undefined;
			isnew = undefined;
			platform = undefined;
			fig = undefined;
			name = undefined;
			uuid = undefined;
			uact = undefined;
			uts = undefined;
			uinfo = undefined;
			this.uid = msgObj.uid;
			this.openid = msgObj.openid;
			this.openkey = msgObj.openkey;
			this.ts = msgObj.ts;
			this.sig = msgObj.sig;
			this.isnew = msgObj.isnew;
			this.platform = msgObj.platform;
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
			if(msgObj.hasOwnProperty("uuid"))
			{
				this.uuid = msgObj.uuid;
			}
			if(msgObj.hasOwnProperty("uact"))
			{
				this.uact = msgObj.uact;
			}
			if(msgObj.hasOwnProperty("uts"))
			{
				this.uts = msgObj.uts;
			}
			if(msgObj.hasOwnProperty("uinfo"))
			{
				this.uinfo = msgObj.uinfo;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):Login
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}