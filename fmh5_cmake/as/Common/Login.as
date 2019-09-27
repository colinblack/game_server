package com.sanguo.game.server.connectlogic.common.message.Common
{
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
		public var isBlueVip:int;
		public var isBlueYearVip:int;
		public var isSuperBlueVip:int;
		public var blueVipLevel:int;
		public var wxChannel:Byte;
		public function Login(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			openid = undefined;
			openkey = undefined;
			ts = undefined;
			sig = undefined;
			isnew = undefined;
			platform = undefined;
			fig = undefined;
			name = undefined;
			isBlueVip = undefined;
			isBlueYearVip = undefined;
			isSuperBlueVip = undefined;
			blueVipLevel = undefined;
			wxChannel = undefined;
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
			if(this.isBlueVip!= undefined)
			{
				serializeObj.isBlueVip = this.isBlueVip;
			}
			if(this.isBlueYearVip!= undefined)
			{
				serializeObj.isBlueYearVip = this.isBlueYearVip;
			}
			if(this.isSuperBlueVip!= undefined)
			{
				serializeObj.isSuperBlueVip = this.isSuperBlueVip;
			}
			if(this.blueVipLevel!= undefined)
			{
				serializeObj.blueVipLevel = this.blueVipLevel;
			}
			if(this.wxChannel!= undefined)
			{
				serializeObj.wxChannel = this.wxChannel.getUint8Array(0, this.wxChannel.length);
				this.wxChannel.pos = 0;
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
			isBlueVip = undefined;
			isBlueYearVip = undefined;
			isSuperBlueVip = undefined;
			blueVipLevel = undefined;
			wxChannel = undefined;
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
			if(msgObj.hasOwnProperty("isBlueVip"))
			{
				this.isBlueVip = msgObj.isBlueVip;
			}
			if(msgObj.hasOwnProperty("isBlueYearVip"))
			{
				this.isBlueYearVip = msgObj.isBlueYearVip;
			}
			if(msgObj.hasOwnProperty("isSuperBlueVip"))
			{
				this.isSuperBlueVip = msgObj.isSuperBlueVip;
			}
			if(msgObj.hasOwnProperty("blueVipLevel"))
			{
				this.blueVipLevel = msgObj.blueVipLevel;
			}
			if(msgObj.hasOwnProperty("wxChannel"))
			{
				this.wxChannel = new Byte();
				this.wxChannel.writeArrayBuffer(msgObj.wxChannel);
				this.wxChannel.pos = 0;
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